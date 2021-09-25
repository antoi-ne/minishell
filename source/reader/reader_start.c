#include "msh.h"
#include "carbon.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void	msh_reader_start(void)
{
	char	*input;
	char	*sinput;
	t_llst	*progs;

	while (1) {
		input = readline(MSH_PROMPT);
		if (input == NULL)
			break;
		if (*input)
			add_history(input);
		
		sinput = str_trim(input, " \t\n\v\f\r");
		progs = NULL;
		msh_parser(sinput, &progs);
		msh_engine_execute(&progs);
		free(sinput);
	}
}
