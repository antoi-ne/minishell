/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 15:31:26 by maperrea          #+#    #+#             */
/*   Updated: 2021/10/13 15:58:06 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "carbon.h"
#include <stdio.h>
#include <fcntl.h>

static void	input(t_lexer *lexer)
{
	int	fd;

	fd = open(lexer->n_token->data, O_RDONLY);
	if (fd < 0)
		utils_exit(EXIT_FAILURE, NULL);
	lexer->c_prog->input = fd;
}

static int	here_doc(t_lexer *lexer)
{
	lexer->c_prog->input = here_document_redirect(lexer->n_token);
	if (lexer->c_prog->input == -1)
		return (-1);
	return (0);
}

static void	output(t_lexer *lexer)
{
	int	fd;

	fd = open(lexer->n_token->data, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
		utils_exit(EXIT_FAILURE, NULL);
	lexer->c_prog->output = fd;
}

static void	output_append(t_lexer *lexer)
{
	int	fd;

	fd = open(lexer->n_token->data, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd < 0)
		utils_exit(EXIT_FAILURE, NULL);
	lexer->c_prog->output = fd;
}

int	msh_parser_redirection(t_lexer *lexer)
{
	if (lexer->n_node == NULL || lexer->n_token->type != TT_WORD)
		return (utils_printerror
			(NULL, "syntax error: no token after redirection"));
	if (str_cmp(lexer->c_token->data, "<") == 0)
		input(lexer);
	else if (str_cmp(lexer->c_token->data, "<<") == 0)
		return (here_doc(lexer));
	else if (str_cmp(lexer->c_token->data, ">") == 0)
		output(lexer);
	else if (str_cmp(lexer->c_token->data, ">>") == 0)
		output_append(lexer);
	return (0);
}
