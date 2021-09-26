#include "msh.h"
#include "carbon.h"

t_llst	*g_msh_env;

int	msh_env_unset(char *key)
{
	t_llst	*node;
	t_llst	*prev;
	t_env	*env;

	node = g_msh_env;
	prev = NULL;
	while (node)
	{
		env = (t_env *)node->data;
		if (str_cmp(env->key, key) == 0)
		{
			if (prev)
				prev->next = node->next;
			else
				g_msh_env = node->next;
			llst_destroy(node, (void (*)(void *)) &msh_env_free);
			return (0);
		}
		prev = node;
		node = node->next;
	}
	return (-1);
}
