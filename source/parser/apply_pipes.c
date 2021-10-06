#include "msh.h"

void	apply_pipes(t_llst **progs)
{
	t_llst	*node;
	t_prog	*prog;
	t_prog	*next_prog;
	int		pipefd[2];

	node = *progs;
	while (node && node->next)
	{
		prog = (t_prog *)node->data;
		next_prog = (t_prog *)node->next->data;
		if (pipe(pipefd) < 0)
			utils_exit(EXIT_FAILURE, NULL);
		if (prog->output == STDOUT_FILENO)
			prog->output = pipefd[1];
		else
			close(pipefd[1]);
		if (next_prog->input == STDIN_FILENO)
			next_prog->input = pipefd[0];
		else
			close(pipefd[0]);
		node = node->next;
	}
}
