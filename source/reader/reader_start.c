#include "msh.h"
#include "carbon.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

extern volatile t_globalstate global_state;

void	msh_reader_start(void)
{
	char	*input;
	char	*tinput;
	t_llst	*progs;

	while (1) {
		input = readline(MSH_PROMPT);
		if (input == NULL)
			break;
		if (*input == '\0')
			continue ;
		global_state.running_subprocess = 1;
		add_history(input);
		tinput = str_trim(input, " \t\n\v\f\r");
		free(input);
		progs = NULL;
		if (msh_parser(tinput, &progs) == -1)
		{
			free (tinput);
			continue ; // leak here (when ctrl-c while here-document)
			           // because parsing is stopped before finishing and not cleared properly
		}
		free (tinput);
		msh_engine_execute(&progs);
		llst_destroyl(&progs, (void (*)(void *)) &msh_parser_prog_free);
		// every data sets needed to apply the input line should be freed, the only section of
		// data that should be keeped between the loop's iterations (the command history) is managed by add_history()
		global_state.running_subprocess = 0;
	}
	printf("exit\n");
	rl_clear_history();
}
