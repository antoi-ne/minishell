#include "msh.h"
#include "carbon.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <signal.h>

static void	execute_builtin_nofork(t_prog *prog)
{
	int		(*def)(t_prog *prog);
	int		ret;

	def = msh_builtins_get(prog->argv[0]);
	ret = def(prog);
	msh_parser_set_retval(ret);
}

void	msh_engine_execute(t_llst **progs)
{
	t_prog	*prog;

	if (llst_len(*progs) == 1)
	{
		prog = (t_prog *)(*progs)->data;
		if (msh_builtins_get(prog->argv[0]))
		{
			execute_builtin_nofork(prog);
			return ;
		}
	}
	execute_all_progs(progs);
}
