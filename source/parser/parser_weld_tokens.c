#include "msh.h"
#include "carbon.h"
#include <stdio.h>

static void	free_tokens(t_token *t_next, t_llst *n_next)
{
	free(t_next->data);
	free(t_next);
	free(n_next);
}

static t_token_type	handle_quote_type(t_token_type type)
{
	if (type == TT_DQS || type == TT_SQS)
		return (TT_WORD);
	return (type);
}

void	msh_parser_weld_tokens(t_llst **tokens)
{
	t_llst	*node;
	t_llst	*n_next;
	t_token	*token;
	t_token	*t_next;
	char	*joined;

	node = *tokens;
	while (node && node->next)
	{
		token = (t_token *)node->data;
		n_next = node->next;
		t_next = (t_token *)n_next->data;
		token->type = handle_quote_type(token->type);
		t_next->type = handle_quote_type(t_next->type);
		if (token->type == TT_WORD && t_next->type == TT_WORD)
		{
			joined = str_join(token->data, t_next->data);
			if (joined == NULL)
				utils_exit(EXIT_FAILURE, NULL);
			free(token->data);
			token->data = joined;
			token->type = TT_WORD;
			node->next = n_next->next;
			free_tokens(t_next, n_next);
		}
		else if (t_next->type == TT_SPCE)
		{
			node->next = n_next->next;
			free_tokens(t_next, n_next);
			node = node->next;
		}
		else
			node = node->next;
	}
	token = (t_token *)node->data;
	token->type = handle_quote_type(token->type);
}
