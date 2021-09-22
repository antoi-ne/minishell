#include "msh.h"
#include "carbon.h"

t_env	*msh_env_get(char *str)
{
	t_llst	*tmp;
	t_env	*data;

	tmp = g_msh_env;
	while (tmp)
	{
		data = tmp->data;
		if (!(str_cmp(data->key, str)))
			return (data);
		tmp = tmp->next;
	}
	return (NULL);
}
