#include "msh.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	signal(SIGINT, sigint_handler);
	msh_env_init(envp);
	msh_reader_start();
}
