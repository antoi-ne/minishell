/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:56:43 by alpeliss          #+#    #+#             */
/*   Updated: 2021/10/13 15:56:44 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "carbon.h"

extern volatile t_globalstate	g_state;

int	msh_env_unset(char *key)
{
	t_llst	*node;
	t_llst	*prev;
	t_env	*env;

	node = g_state.env;
	prev = NULL;
	while (node)
	{
		env = (t_env *)node->data;
		if (str_cmp(env->key, key) == 0)
		{
			if (prev)
				prev->next = node->next;
			else
				g_state.env = node->next;
			llst_destroy(node, (void (*)(void *)) & msh_env_free);
			return (0);
		}
		prev = node;
		node = node->next;
	}
	return (-1);
}
