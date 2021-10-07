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

void	msh_reader_start(int err)
{
	char	*input;
	t_llst	*progs;

	while (1)
	{
		input = readline(MSH_PROMPT);
		if (input == NULL)
			break ;
		if (*input == '\0')
			continue ;
		g_state.running_subprocess = 1;
		add_history(input);
		input = trim_input(input);
		progs = NULL;
		err = msh_parser(input, &progs);
		free (input);
		if (err == -1)
		{
			g_state.running_subprocess = 0;
			continue ;
		}
		msh_engine_execute(&progs);
		llst_destroyl(&progs, (void (*)(void *)) & msh_parser_prog_free);
		g_state.running_subprocess = 0;
	}
	printf("exit\n");
	rl_clear_history();
}

/*
** leak here (when ctrl-c while here-document)
** because parsing is stopped before finishing and not cleared properly	
** every data sets needed to apply the input line should be freed, 
** the only section of data that should be keeped between the loop's iterations 
** (the command history) is managed by add_history()
*/
