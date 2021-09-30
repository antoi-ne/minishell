#include "msh.h"
#include "carbon.h"
#include <stdio.h>

void	msh_parser_token_free(t_token *token)
{
	free(token->data);
	free(token);
}

void	msh_parser_prog_free(t_prog *prog)
{
	size_t	i;

	// printf("freeing prog %s:\n", prog->argv[0]);
	i = 0;
	while (prog->argv[i])
	{
		free(prog->argv[i]);
		i++;
	}
	free(prog->argv);
	free(prog);
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

int	msh_parser(char *input, t_llst **progs)
{
	t_llst	*tokens;

	tokens = NULL;
	*progs = NULL;
	msh_parser_tokenize(input, &tokens);
	msh_parser_expand(&tokens);
	msh_parser_weld_tokens(&tokens);
	if (msh_parser_lexer(&tokens, progs) == -1)
		return (-1);
	llst_destroyl(&tokens, (void (*)(void *)) &msh_parser_token_free);
	return (0);
}
