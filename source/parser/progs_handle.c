/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progs_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:58:11 by alpeliss          #+#    #+#             */
/*   Updated: 2021/10/13 15:58:14 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "stdio.h"

t_prog	*init_prog(void)
{
	t_prog	*prog;

	prog = mem_calloc(sizeof(t_prog));
	if (prog == NULL)
		utils_exit(EXIT_FAILURE, NULL);
	prog->argv = NULL;
	prog->input = STDIN_FILENO;
	prog->output = STDOUT_FILENO;
	return (prog);
}

void	print_progs(t_llst *progs)
{
	t_llst	*node;
	t_prog	*prog;
	size_t	i;

	node = progs;
	while (node)
	{
		prog = (t_prog *)node->data;
		printf("prog %p {\n    argv:", prog);
		i = 0;
		while (prog->argv[i])
		{
			printf(" %s", prog->argv[i]);
			i++;
		}
		printf("\n    input: %d\n    output: %d\n}\n", prog->input, prog->output);
		node = node->next;
	}
}
