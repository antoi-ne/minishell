/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:56:37 by alpeliss          #+#    #+#             */
/*   Updated: 2021/10/13 15:56:39 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "carbon.h"

extern volatile t_globalstate	g_state;

static t_env	*env_new(void)
{
	t_env	*entry;

	entry = mem_calloc(sizeof(t_env));
	if (!entry)
		utils_exit(EXIT_FAILURE, "memory allocation error");
	return (entry);
}

void	msh_env_set(char *key, char *def)
{
	t_env	*env;
	t_llst	*node;

	env = msh_env_get(key);
	if (env == NULL)
	{
		env = env_new();
		env->key = str_dup(key);
		if (env->key == NULL)
			utils_exit(EXIT_FAILURE, "memory allocation error");
		env->def = str_dup(def);
		if (env->def == NULL)
			utils_exit(EXIT_FAILURE, "memory allocation error");
		node = llst_new(env);
		if (node == NULL)
			utils_exit(EXIT_FAILURE, "memory allocation error");
		llst_push((t_llst **)&g_state.env, node);
	}
	else
	{
		free(env->def);
		env->def = str_dup(def);
		if (env->def == NULL)
			utils_exit(EXIT_FAILURE, "memory allocation error");
	}
}
