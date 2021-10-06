#include "msh.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int	utils_printerror(char *prog, char *msg)
{
	if (prog)
		printf("msh: %s: %s\n", prog, msg);
	else
		printf("msh: %s\n", msg);
	return (1);
}
