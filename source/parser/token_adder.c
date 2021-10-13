/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_adder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:58:43 by alpeliss          #+#    #+#             */
/*   Updated: 2021/10/13 15:58:45 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	add_dqs_token(char *input, t_llst **tokens, size_t *i)
{
	size_t	marker;
	char	*token;

	marker = *i;
	*i = *i + 1;
	while (input[*i] && input[*i] != '"')
		*i = *i + 1;
	if (input[*i] == '\0')
		return (utils_printerror
			(NULL, "syntax error: unclosed double quote string"));
	token = str_sub(input, marker + 1, *i - marker - 1);
	if (token == NULL)
		utils_exit(EXIT_FAILURE, NULL);
	add_token(tokens, token, TT_DQS);
	*i = *i + 1;
	return (0);
}

int	add_sqs_token(char *input, t_llst **tokens, size_t *i)
{
	size_t	marker;
	char	*token;

	marker = *i;
	*i = *i + 1;
	while (input[*i] && input[*i] != '\'')
		*i = *i + 1;
	if (input[*i] == '\0')
		return (utils_printerror
			(NULL, "syntax error: unclosed single quote string"));
	token = str_sub(input, marker + 1, *i - marker - 1);
	if (token == NULL)
		utils_exit(EXIT_FAILURE, NULL);
	add_token(tokens, token, TT_SQS);
	*i = *i + 1;
	return (0);
}

int	add_redirect_token(char *input, t_llst **tokens, size_t *i)
{
	size_t	marker;
	char	*token;

	marker = *i;
	while (input[*i] && (input[*i] == input[marker]))
		*i = *i + 1;
	if (*i - marker > 2)
		return (utils_printerror(NULL, "syntax error: invalid token"));
	token = str_sub(input, marker, *i - marker);
	if (token == NULL)
		utils_exit(EXIT_FAILURE, NULL);
	add_token(tokens, token, TT_RERD);
	return (0);
}

int	add_pipe_token(char *input, t_llst **tokens, size_t *i)
{
	size_t	marker;
	char	*token;

	marker = *i;
	while (input [*i] && input[*i] == '|')
		*i = *i + 1;
	if (*i - marker > 2)
		return (utils_printerror
			(NULL, "syntax error: multiple trailing pipes"));
	token = str_dup("|");
	if (token == NULL)
		utils_exit(EXIT_FAILURE, NULL);
	add_token(tokens, token, TT_PIPE);
	return (0);
}

void	add_word_token(char *input, t_llst **tokens, size_t *i)
{
	size_t	marker;
	char	*token;

	marker = *i;
	*i = *i + 1;
	while (input[*i] && input[*i] != ' ' && input[*i] != '"'
		&& input[*i] != '\'' && input[*i] != '<' && input[*i] != '>'
		&& input[*i] != '$' && input[*i] != '|')
		*i = *i + 1;
	token = str_sub(input, marker, *i - marker);
	if (token == NULL)
		utils_exit(EXIT_FAILURE, NULL);
	add_token(tokens, token, TT_WORD);
}
