#include "msh.h"
#include "carbon.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

extern volatile t_globalstate	g_state;

static char	*trim_input(char *input)
{
	char	*new_input;

	new_input = str_trim(input, " \t\n\v\f\r");
	free(input);
	return (new_input);
}

static int	free_and_return(t_llst **progs)
{
	llst_destroyl(progs, (void (*)(void *)) & msh_parser_prog_free);
	return (0);
}

static int	read_line(char *input, t_llst **progs, int *err)
{
	input = readline(MSH_PROMPT);
	if (input == NULL)
		return (1);
	if (*input == '\0')
		return (0);
	g_state.running_subprocess = 1;
	add_history(input);
	input = trim_input(input);
	if (input[0] == '\0')
	{
		free(input);
		return (0);
	}
	*progs = NULL;
	*err = msh_parser(input, progs);
	free (input);
	if (*err == -1)
		return (free_and_return(progs));
	g_state.running_subprocess = 1;
	msh_engine_execute(progs);
	llst_destroyl(progs, (void (*)(void *)) & msh_parser_prog_free);
	g_state.running_subprocess = 0;
	return (0);
}

void	msh_reader_start(void)
{
	char	*input;
	t_llst	*progs;
	int		err;

	input = NULL;
	while (1)
	{
		if (read_line(input, &progs, &err))
			break ;
	}
	rl_clear_history();
}
