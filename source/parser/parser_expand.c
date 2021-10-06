#include "msh.h"
#include "carbon.h"
#include <stdio.h>

static char	*find_one_char_expanded(t_llst *node)
{
	char	*expanded;

	if (node->next == NULL
		|| (((t_token *)node->next->data)->type != TT_DQS
			&& ((t_token *)node->next->data)->type != TT_SQS))
		expanded = str_dup("$");
	else
		expanded = str_dup("");
	return (expanded);
}

static char	*find_env_expanded(char *data)
{
	char	*expanded;
	t_env	*var;

	var = msh_env_get(data);
	if (var == NULL)
		expanded = str_dup("");
	else
		expanded = str_dup(var->def);
	return (expanded);
}

static char	*find_word_expanded(t_llst *node, t_token *token)
{
	char	*expanded;

	if (token->data[1] == '\0')
		expanded = find_one_char_expanded(node);
	else if (str_cmp(token->data + 1, "?") == 0)
		expanded = types_int2str(msh_parser_get_retval());
	else
		expanded = find_env_expanded(token->data + 1);
	if (expanded == NULL)
		utils_exit(EXIT_FAILURE, NULL);
	return (expanded);
}

void	msh_parser_expand(t_llst **tokens)
{
	t_llst	*node;
	t_token	*token;
	char	*expanded;

	node = *tokens;
	while (node)
	{
		token = (t_token *)node->data;
		if (token->type == TT_WORD && token->data[0] == '$')
		{
			expanded = find_word_expanded(node, token);
			free(token->data);
			token->data = expanded;
		}
		else if (token->type == TT_DQS)
		{
			expanded = msh_parser_expand_dqs(token->data, 0, 0);
			token->data = expanded;
		}
		node = node->next;
	}
}
