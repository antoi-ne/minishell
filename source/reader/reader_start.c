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

	while (1) {
		input = readline(MSH_PROMPT);
		if (input == NULL)
			break;
		if (*input)
			add_history(input);
		
		sinput = str_trim(input, " \t\n\v\f\r");
		msh_parser_tokenize(sinput);
		free (sinput);
	}
}
