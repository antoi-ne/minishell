#include "msh.h"
#include "carbon.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <signal.h>

static void	execute_builtins(t_prog *prog)
{
	int		(*def)(t_prog *prog);

	def = msh_builtins_get(prog->argv[0]);
	def(prog);
}

void	msh_engine_execute(t_llst **progs)
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
			execute_builtins(prog);
		else
		{
			cmd = msh_check_path(prog->argv[0]);
			if (cmd == NULL)
				utils_exit(EXIT_FAILURE, "Command not found");
			pid = fork();
			if (pid < 0)
				utils_exit(EXIT_FAILURE, "Fork error");
			else if (pid == 0)
			{
				// signal(SIGINT, NULL);
				dup2(prog->input, STDIN_FILENO);
				dup2(prog->output, STDOUT_FILENO);
				retval = execve(cmd, prog->argv, msh_env_all());
				if (prog->input > 2)
					close(prog->input);
				if (prog->output > 2)
					close(prog->output);
				exit (retval);
			}
			else
			{
				free(cmd);
				if (prog->input > 2)
					close(prog->input);
				if (prog->output > 2)
					close(prog->output);
				if (node->next == NULL)
				{
					waitpid(pid, &retval, 0);
				}
			}
		}
		node = node->next;
	}
}
