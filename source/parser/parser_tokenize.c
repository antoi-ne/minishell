#include "msh.h"
#include "carbon.h"
#include "stdio.h"

void	add_token(t_llst **tokens, char *data, t_token_type type)
{
	t_token	*token;
	t_llst	*node;

	token = mem_calloc(sizeof(t_token));
	if (token == NULL)
		utils_exit(EXIT_FAILURE, "memory allocation error");
	token->data = data;
	token->type = type;
	node = llst_new(token);
	if (node == NULL)
		utils_exit(EXIT_FAILURE, "memory allocation error");
	llst_push(tokens, node);
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

void	msh_parser_tokenize(char *input)
{
	size_t	i;
	size_t	marker;
	char	*token;
	t_llst	*tokens;

	i = 0;
	tokens = NULL;
	while (input[i])
	{
		if (input[i] == ' ')
		{
			token = str_dup(" ");
			if (token == NULL)
				utils_exit(EXIT_FAILURE, "memory allocation error");
			add_token(&tokens, token, TT_SPCE);
			i++;
			while (input[i] && input[i] == ' ')
				i++;
		}
		else if (input[i] == '"')
		{
			marker = i;
			i++;
			while (input[i] && input[i] !='"')
				i++;
			if (input[i] == '\0')
				utils_exit(EXIT_FAILURE, "unclosed double quote string");
			token = str_sub(input, marker + 1, i - marker);
			add_token(&tokens, token, TT_DQS);
			i++;
		}
		else if (input[i] == '\'')
		{
			marker = i;
			i++;
			while (input[i] && input[i] !='\'')
				i++;
			if (input[i] == '\0')
				utils_exit(EXIT_FAILURE, "unclosed single quote string");
			token = str_sub(input, marker + 1, i - marker - 1);
			add_token(&tokens, token, TT_SQS);
			i++;
		}
		else
		{
			marker = i;
			while (input[i] && input[i] != ' ' && input[i] != '"' && input[i] != '\'')
				i++;
			token = str_sub(input, marker, i - marker - 1);
			add_token(&tokens, token, TT_WORD);
		}
	}
	print_tokens(tokens);
}
