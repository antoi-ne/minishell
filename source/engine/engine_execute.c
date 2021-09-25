#include "msh.h"
#include "carbon.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void	msh_engine_execute(t_llst **progs)
{
	t_llst	*node;
	t_prog	*prog;
	char	*cmd;
	pid_t	pid;

	node = *progs;
	while (node)
	{
		prog = (t_prog *)node->data;
		cmd = msh_check_path(prog->argv[0]);
		if (cmd == NULL)
			utils_exit(EXIT_FAILURE, "Command not found");
		pid = fork();
		if (pid < 0)
			utils_exit(EXIT_FAILURE, "Fork error");
		else if (pid == 0)
		{
			dup2(prog->input, STDIN_FILENO);
			dup2(prog->output, STDOUT_FILENO);
			execve(cmd, prog->argv, msh_env_all());
		}
		else
			waitpid(pid, NULL, 0);
		node = node->next;
	}
}
