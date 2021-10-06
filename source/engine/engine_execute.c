#include "msh.h"
#include "carbon.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <signal.h>

static void	prog_close_fds(t_prog *prog)
{
	if (prog->input != STDIN_FILENO)
		close(prog->input);
	if (prog->output != STDOUT_FILENO)
		close(prog->output);
}

static void	execute_builtin_nofork(t_prog *prog)
{
	int		(*def)(t_prog *prog);

	def = msh_builtins_get(prog->argv[0]);
	def(prog);
}

static void	execute_all_progs(t_llst **progs)
{
	t_llst	*node;
	t_prog	*prog;
	char	*cmd;
	pid_t	pid;
	int		retval;

	node = *progs;
	while (node)
	{
		prog = (t_prog *)node->data;
		if (msh_builtins_get(prog->argv[0]))
		{
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
		else
		{
			cmd = msh_check_path(prog->argv[0]);
			if (cmd == NULL)
			{
				utils_printerror(prog->argv[0], "command not found");
				prog_close_fds(prog);
				msh_parser_set_retval(127);
				node = node->next;
				continue;
			}
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
		node = node->next;
	}
}

void	msh_engine_execute(t_llst **progs)
{
	t_prog	*prog;
	if (llst_len(*progs) == 1)
	{
		prog = (t_prog *)(*progs)->data;
		if (msh_builtins_get(prog->argv[0]) == &msh_builtins_exit)
		{
			execute_builtin_nofork(prog);
			return ;
		}
	}
	execute_all_progs(progs);
}
