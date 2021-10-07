#include "msh.h"

static void	prog_close_fds(t_prog *prog)
{
	if (prog->input != STDIN_FILENO)
		close(prog->input);
	if (prog->output != STDOUT_FILENO)
		close(prog->output);
}

static void	execute_builtin(t_llst *node, t_prog *prog)
{
	pid_t	pid;
	int		retval;

	pid = fork();
	if (pid < 0)
		utils_exit(EXIT_FAILURE, NULL);
	else if (pid == 0)
	{
		if (dup2(prog->input, STDIN_FILENO) < 0)
			exit(EXIT_FAILURE);
		if (dup2(prog->output, STDOUT_FILENO) < 0)
			exit(EXIT_FAILURE);
		prog_close_fds(prog);
		retval = msh_builtins_get(prog->argv[0])(prog);
		msh_parser_prog_free(prog);
		exit(retval);
	}
	else
	{
		prog_close_fds(prog);
		if (node->next == NULL)
		{
			waitpid(pid, &retval, 0);
			msh_parser_set_retval(WEXITSTATUS(retval));
		}
	}
}

static void	execute_binary(t_llst *node, t_prog *prog, char *cmd)
{
	pid_t	pid;
	int		retval;

	pid = fork();
	if (pid < 0)
		utils_exit(EXIT_FAILURE, NULL);
	else if (pid == 0)
	{
		if (dup2(prog->input, STDIN_FILENO) < 0
			|| dup2(prog->output, STDOUT_FILENO) < 0)
			exit(EXIT_FAILURE);
		prog_close_fds(prog);
		retval = execve(cmd, prog->argv, msh_env_all());
		exit (retval);
	}
	else
	{
		free(cmd);
		prog_close_fds(prog);
		if (node->next == NULL)
		{
			waitpid(pid, &retval, 0);
			msh_parser_set_retval(WEXITSTATUS(retval));
		}
	}
}

void	execute_all_progs(t_llst **progs)
{
	t_llst	*node;
	t_prog	*prog;
	char	*cmd;

	node = *progs;
	while (node)
	{
		prog = (t_prog *)node->data;
		if (msh_builtins_get(prog->argv[0]))
			execute_builtin(node, prog);
		else
		{
			cmd = msh_check_path(prog->argv[0], -1);
			if (cmd)
				execute_binary(node, prog, cmd);
			else
			{
				utils_printerror(prog->argv[0], "command not found");
				prog_close_fds(prog);
				msh_parser_set_retval(127);
				return ;
			}
		}
		node = node->next;
	}
}
