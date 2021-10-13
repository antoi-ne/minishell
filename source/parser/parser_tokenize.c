/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokenize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:57:19 by alpeliss          #+#    #+#             */
/*   Updated: 2021/10/13 15:57:21 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	add_space_token(char *input, t_llst **tokens, size_t *i)
{
	char	*token;

	token = str_dup(" ");
	if (token == NULL)
		utils_exit(EXIT_FAILURE, NULL);
	add_token(tokens, token, TT_SPCE);
	*i = *i + 1;
	while (input[*i] && input[*i] == ' ')
		*i = *i + 1;
}

int	msh_parser_tokenize(char *input, t_llst **tokens)
{
	size_t	i;
	int		err;

	i = 0;
	err = 0;
	while (input[i])
	{
		if (input[i] == ' ')
			add_space_token(input, tokens, &i);
		else if (input[i] == '"')
			err = add_dqs_token(input, tokens, &i);
		else if (input[i] == '\'')
			err = add_sqs_token(input, tokens, &i);
		else if (input[i] == '<' || input[i] == '>')
			err = add_redirect_token(input, tokens, &i);
		else if (input[i] == '|')
			err = add_pipe_token(input, tokens, &i);
		else
			add_word_token(input, tokens, &i);
		if (err)
			return (err);
	}
	return (0);
}
