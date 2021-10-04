#include "msh.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int	utils_exit(int ec, char *err_msg)
{
		if (ec != EXIT_SUCCESS)
	{
		if (err_msg == NULL)
			perror("msh");
		else
			printf("msh: %s\n", err_msg);
	}
	exit(ec);
}
