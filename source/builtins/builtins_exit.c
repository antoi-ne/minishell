#include "msh.h"
#include "carbon.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>

int		msh_builtins_exit(t_prog *prog)
{
	(void)prog;
	printf("exit\n");
	rl_clear_history();
	exit(EXIT_SUCCESS);
}
