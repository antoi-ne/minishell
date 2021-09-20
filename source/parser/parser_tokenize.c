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

// void	parser_dquotes(t_llst **tokens, char *input)
// {
// 	size_t	i;
// 	size_t	marker;
// 	char	*string_token;

// 	i = 0;
// 	while (input[i])
// 	{
// 		if (input[i] == '"')
// 		{
// 			marker = i;
// 			i++;
// 			while (input[i] && input[i] != '"')
// 				i++;
// 			if (input[i] == '\0')
// 				utils_exit(EXIT_FAILURE, "unclosed string");
// 			string_token = str_sub(input, marker, i - marker + 1);
// 			printf("found dqs: [%s]\n", string_token);
// 			// add_token(tokens, string_token, TT_DQS);
// 			(void)tokens;
// 		}
// 		i++;
// 	}
// }

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
	t_llst	*tokens;
	size_t	i;
	size_t	marker;
	char	*token;

	i = 0;
	while (input[i])
	{
		if (input[i] == '"')
		{
			marker = i;
			while (input[i] && input[i] != '"')
				i++;
			if (input[i] == '\0')
				utils_exit(EXIT_FAILURE, "unclosed string");
			token = str_sub(input, marker, i - marker + 1);
			add_token(&tokens, token, TT_DQS);
		}
		else if (input[i] == '\'')
		{
			marker = i;
			while (input[i] && input[i] != '\'')
				i++;
			if (input[i] == '\0')
				utils_exit(EXIT_FAILURE, "unclosed string");
			token = str_sub(input, marker, i - marker + 1);
			add_token(&tokens, token, TT_SQS);
		}
		else if (input[i] != ' ')
		{
			marker = i;
			while (input[i] && input[i] != ' ')
				i++;
			token = str_sub(input, marker, i - marker + 1);
			add_token(&tokens, token, TT_UKWN);
		}
		i++;
	}
	print_tokens(tokens);
}
