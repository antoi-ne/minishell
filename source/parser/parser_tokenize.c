#include "msh.h"
#include "carbon.h"
#include <stdio.h>

void	add_token(t_llst **tokens, char *data, t_token_type type)
{
	t_token	*token;
	t_llst	*node;

	token = mem_calloc(sizeof(t_token));
	if (token == NULL)
		utils_exit(EXIT_FAILURE, NULL);
	token->data = data;
	token->type = type;
	node = llst_new(token);
	if (node == NULL)
		utils_exit(EXIT_FAILURE, NULL);
	token->is_string = 0;
	if (type == TT_DQS || type == TT_SQS)
		token->is_string = 1;
	llst_push(tokens, node);
}

void	msh_parser_tokenize(char *input, t_llst **tokens)
{
	size_t	i;
	size_t	marker;
	char	*token;

	i = 0;
	while (input[i])
	{
		if (input[i] == ' ')
		{
			token = str_dup(" ");
			if (token == NULL)
				utils_exit(EXIT_FAILURE, NULL);
			add_token(tokens, token, TT_SPCE);
			if (token == NULL)
				utils_exit(EXIT_FAILURE, NULL);
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
			token = str_sub(input, marker + 1, i - marker - 1);
			if (token == NULL)
				utils_exit(EXIT_FAILURE, NULL);
			add_token(tokens, token, TT_DQS);
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
			if (token == NULL)
				utils_exit(EXIT_FAILURE, NULL);
			add_token(tokens, token, TT_SQS);
			i++;
		}
		else if (input[i] == '<' || input[i] == '>')
		{
			marker = i;
			while (input[i] && (input[i] == input[marker]))
				i++;
			if (i - marker > 2)
				utils_exit(EXIT_FAILURE, "parsing error: invalid redirection token");
			token = str_sub(input, marker, i - marker);
			if (token == NULL)
				utils_exit(EXIT_FAILURE, NULL);
			add_token(tokens, token, TT_RERD);
		}
		else if (input[i] == '|')
		{
			marker = i;
			while (input [i] && input[i] == '|')
				i ++;
			if (i - marker > 2)
				utils_exit(EXIT_FAILURE, "parsing error: multiple trailing pipes");
			token = str_dup("|");
			if (token == NULL)
				utils_exit(EXIT_FAILURE, NULL);
			add_token(tokens, token, TT_PIPE);
		}
		else
		{
			marker = i;
			i++;
			while (input[i] && input[i] != ' ' && input[i] != '"' && input[i] != '\'' && input[i] != '<' && input[i] != '>' && input[i] != '$' && input[i] != '|')
				i++;
			token = str_sub(input, marker, i - marker);
			if (token == NULL)
				utils_exit(EXIT_FAILURE, NULL);
			add_token(tokens, token, TT_WORD);
		}
	}
}
