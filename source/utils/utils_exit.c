#include "msh.h"
#include <stdlib.h>
#include <stdio.h>

int	utils_exit(int ec, char *err_msg)
{
	if (ec != EXIT_SUCCESS)
		printf("msh: %s\n", err_msg);
	exit(ec);
}
