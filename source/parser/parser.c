#include "msh.h"
#include "carbon.h"
#include <stdio.h>

void	msh_parser(char *input, t_llst **progs)
{
	t_llst	*tokens;

	tokens = NULL;
	*progs = NULL;
	msh_parser_tokenize(input, &tokens);
	msh_parser_expand(&tokens);
	msh_parser_weld_tokens(&tokens);
	msh_parser_lexer(&tokens, progs);
}
