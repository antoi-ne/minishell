#include "msh.h"
#include "carbon.h"

t_llst	*g_msh_env;

t_env	*msh_env_get(char *key)
{
	t_llst	*tmp;
	t_env	*data;

	tmp = g_msh_env;
	while (tmp)
	{
		data = tmp->data;
		if (!(str_cmp(data->key, key)))
			return (data);
		tmp = tmp->next;
	}
	return (NULL);
}
