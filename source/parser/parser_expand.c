#include "msh.h"
#include "carbon.h"
#include <stdio.h>

static char	*dqs_newstr(char *str, char *expanded, size_t start, size_t end)
{
	size_t	i;
	size_t	j;
	char	*new;

	i = 0;
	new = mem_calloc(sizeof(char) * (str_len(str) - (end - start) + str_len(expanded) + 1));
	if (new == NULL)
		utils_exit(EXIT_FAILURE, "memory allocation error");
	while (i < start)
	{
		new[i] = str[i];
		i++;
	}
	j = 0;
	while (j < str_len(expanded))
	{
		new[i] = expanded[j];
		i++;
		j++;
	}
	j = end;
	while (str[j])
	{
		new[i] = str[j];
		i++;
		j++;
	}
	return (new);
}

static char	*expand_dqs(char *str)
{
	size_t	i;
	size_t	start;
	char	*vn;
	t_env	*var;
	char	*expanded;
	char	*new;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			start = i;
			i++;
			while (str[i] && str[i] != ' ' && str[i] != '$')
			{
				i++;
			}
			vn = str_sub(str, start + 1, i - start - 1);
			var = msh_env_get(vn);
			free(vn);
			if (var == NULL)
				expanded = str_dup("");
			else
				expanded = str_dup(var->def);
			if (expanded == NULL)
				utils_exit(EXIT_FAILURE, "memory allocation error");
			new = dqs_newstr(str, expanded, start, i);
			free(str);
			str = new;
			i = start + str_len(expanded) - 1;
			free(expanded);
		}
		i++;
	}
	return (str);
}

void	msh_parser_expand(t_llst **tokens)
{
	t_llst	*node;
	t_token	*token;
	t_env	*var;
	char	*expanded;

	node = *tokens;
	while (node)
	{
		token = (t_token *)node->data;
		if (token->type == TT_WORD && token->data[0] == '$')
		{
			var = msh_env_get(token->data + 1);
			if (var == NULL)
				expanded = str_dup("");
			else
				expanded = str_dup(var->def);
			if (expanded == NULL)
				utils_exit(EXIT_FAILURE, "memory allocation error");
			free(token->data);
			token->data = expanded;
		}
		else if (token->type == TT_DQS)
		{
			expanded = expand_dqs(token->data);
			token->data = expanded;
		}
		node = node->next;
	}
}
