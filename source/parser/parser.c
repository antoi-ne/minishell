#include "msh.h"
#include "carbon.h"
#include <stdio.h>

void	token_free(t_token *token)
{
	free(token->data);
	free(token);
}

void	print_tokens(t_llst	*tokens)
{
	t_llst	*node;
	t_token	*token;

	node = tokens;
	while (node != NULL)
	{
		token = (t_token *)node->data;
		printf("(%d) [%s]\n", token->type, token->data);
		node = node->next;
	}
}

void	msh_parser(char *input, t_llst **progs)
{
	t_llst	*tokens;

	tokens = NULL;
	*progs = NULL;
	msh_parser_tokenize(input, &tokens);
	msh_parser_expand(&tokens);
	msh_parser_weld_tokens(&tokens);
	msh_parser_lexer(&tokens, progs);
	llst_destroyl(&tokens, (void (*)(void *)) &token_free);
}
