#include "msh.h"
#include "carbon.h"
#include <stdlib.h>
#include <stdio.h>

int		msh_builtins_exit(t_prog *prog)
{
	(void)prog;
	printf("gonna exit real quick\n");
	exit(EXIT_SUCCESS);
}
