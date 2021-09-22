#include "msh.h"
#include "carbon.h"
#include <stdio.h>

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
		if (token->type == TT_DQS || token->type == TT_SQS)
			token->type = TT_WORD;
		if (t_next->type == TT_DQS || t_next->type == TT_SQS)
			t_next->type = TT_WORD;
		if (token->type == TT_WORD && t_next->type == TT_WORD)
		{
			joined = str_join(token->data, t_next->data);
			if (joined == NULL)
				utils_exit(EXIT_FAILURE, "memory allocation error");
			free(token->data);
			token->data = joined;
			token->type = TT_WORD;
			node->next = n_next->next;
			free(t_next->data);
			free(t_next);
			free(n_next);
		}
		else
			node = node->next;
	}
}