#include "msh.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	msh_env_init(envp);
	msh_reader_start();
}
