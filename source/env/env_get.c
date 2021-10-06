#include "msh.h"
#include "carbon.h"

extern volatile t_globalstate global_state;

t_env	*msh_env_get(char *key)
{
	t_llst	*tmp;
	t_env	*data;

	tmp = global_state.env;
	while (tmp)
	{
		data = tmp->data;
		if (!(str_cmp(data->key, key)))
			return (data);
		tmp = tmp->next;
	}
	return (NULL);
}
