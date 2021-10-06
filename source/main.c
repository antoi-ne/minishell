#include "msh.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>
#include <errno.h>

t_globalstate	g_state = {0, 0, NULL};

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	if (g_state.running_subprocess == 0)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	msh_env_init(envp);
	msh_reader_start(0);
	exit(EXIT_SUCCESS);
}
/*
**  msh_env_set("GAMING", "teststring");
*/
