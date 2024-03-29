/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:58:00 by alpeliss          #+#    #+#             */
/*   Updated: 2021/10/13 15:58:01 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "carbon.h"
#include <stdio.h>

void	msh_parser_token_free(t_token *token)
{
	free(token->data);
	free(token);
}

void	msh_parser_prog_free(t_prog *prog)
{
	size_t	i;

	i = 0;
	while (prog->argv[i])
	{
		free(prog->argv[i]);
		i++;
	}
	free(prog->argv);
	free(prog);
}

int	msh_parser(char *input, t_llst **progs)
{
	t_llst	*tokens;

	tokens = NULL;
	*progs = NULL;
	if (msh_parser_tokenize(input, &tokens) != 0)
	{
		llst_destroyl(&tokens, (void (*)(void *)) & msh_parser_token_free);
		return (-1);
	}
	msh_parser_expand(&tokens);
	msh_parser_weld_tokens(&tokens);
	if (msh_parser_lexer(&tokens, progs) != 0)
	{
		llst_destroyl(&tokens, (void (*)(void *)) & msh_parser_token_free);
		return (-1);
	}
	llst_destroyl(&tokens, (void (*)(void *)) & msh_parser_token_free);
	return (0);
}
