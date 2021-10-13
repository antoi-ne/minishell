/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 17:59:30 by maperrea          #+#    #+#             */
/*   Updated: 2021/10/13 15:56:31 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "carbon.h"
#include <stdio.h>

extern volatile t_globalstate	g_state;

static t_env	*env_new(void)
{
	t_env	*entry;

	entry = mem_calloc(sizeof(t_env));
	if (!entry)
		utils_exit(EXIT_FAILURE, "memory allocation error");
	return (entry);
}

void	adjust_shell_level(void)
{
	int		new_level;
	t_env	*shlvl;
	char	*to_free;

	shlvl = msh_env_get("SHLVL");
	if (shlvl == NULL || *(shlvl->def) == '\0' || !utils_is_number(shlvl->def))
		new_level = 1;
	else
		new_level = types_str2int(shlvl->def) + 1;
	if (new_level < 0)
		new_level = 0;
	else if (new_level >= 1000)
	{
		fmt_fprint(2, "msh: shell level (");
		to_free = types_int2str(new_level);
		fmt_fprint(2, to_free);
		free(to_free);
		fmt_fprint(2, ") too high, resetting to 1\n");
		new_level = 1;
	}
	to_free = types_int2str(new_level);
	msh_env_set("SHLVL", to_free);
	free(to_free);
}

void	msh_env_init(char **envp)
{
	size_t	i;
	size_t	key_len;
	t_env	*entry;
	t_llst	*node;

	i = 0;
	while (envp[i])
	{
		entry = env_new();
		key_len = 0;
		while (envp[i][key_len] != '=')
			key_len++;
		entry->key = str_sub(envp[i], 0, key_len);
		if (!entry->key)
			utils_exit(EXIT_FAILURE, "memory allocation error");
		entry->def = str_sub(envp[i], key_len + 1, str_len(envp[i]));
		if (!entry->def)
			utils_exit(EXIT_FAILURE, "memory allocation error");
		node = llst_new(entry);
		if (!node)
			utils_exit(EXIT_FAILURE, "memory allocation error");
		llst_push((t_llst **)&g_state.env, node);
		i++;
	}
	adjust_shell_level();
}

// void	env_print(void)
// {
// 	t_llst	*node;

// 	node = g_msh_env;
// 	while (node)
// 	{
// 		printf("%s = %s\n", ((t_env *)node->data)->key, 
// 		((t_env *)node->data)->def);
// 		node = node->next;
// 	}
// }
