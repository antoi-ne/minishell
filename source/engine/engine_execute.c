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

	node = *progs;
	while (node)
	{
		prog = (t_prog *)node->data;

		node = node->next;
	}
}
