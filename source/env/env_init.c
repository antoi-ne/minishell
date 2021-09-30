#include "msh.h"
#include "carbon.h"
#include <stdio.h>

t_llst	*g_msh_env;

static t_env	*env_new(void)
{
	t_env	*entry;

	entry = mem_calloc(sizeof(t_env));
	if (!entry)
		utils_exit(EXIT_FAILURE, "memory allocation error");
	return (entry);
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
		llst_push(msh_env_var(), node);
		i++;
	}
}

// void	env_print(void)
// {
// 	t_llst	*node;

// 	node = g_msh_env;
// 	while (node)
// 	{
// 		printf("%s = %s\n", ((t_env *)node->data)->key, ((t_env *)node->data)->def);
// 		node = node->next;
// 	}
// }
