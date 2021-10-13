/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_all.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:56:10 by alpeliss          #+#    #+#             */
/*   Updated: 2021/10/13 15:56:11 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "carbon.h"
#include <stdio.h>

extern volatile t_globalstate	g_state;

char	**msh_env_all(void)
{
	char	**envp;
	size_t	len;
	size_t	i;
	t_llst	*node;

	len = llst_len(g_state.env);
	envp = mem_calloc(sizeof(char *) * (len + 1));
	if (!envp)
		utils_exit(EXIT_FAILURE, "memory allocation error");
	i = 0;
	node = g_state.env;
	while (i < len)
	{
		envp[i] = mem_calloc(str_len(((t_env *)node->data)->key)
				+ str_len(((t_env *)node->data)->def) + 2);
		if (!envp[i])
			utils_exit(EXIT_FAILURE, "memory allocation error");
		str_cat(envp[i], ((t_env *)node->data)->key);
		str_cat(envp[i], "=");
		str_cat(envp[i], ((t_env *)node->data)->def);
		node = node->next;
		i++;
	}
	return (envp);
}
