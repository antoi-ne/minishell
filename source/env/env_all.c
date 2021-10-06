#include "msh.h"
#include "carbon.h"
#include <stdio.h>

extern volatile t_globalstate global_state;

char **msh_env_all(void)
{
	char	**envp;
	size_t	len;
	size_t	i;
	t_llst	*node;

	len = llst_len(global_state.env);
	envp = mem_calloc(sizeof(char *) * (len + 1));
	if (!envp)
		utils_exit(EXIT_FAILURE, "memory allocation error");
	i = 0;
	node = global_state.env;
	while (i < len)
	{
		envp[i] = mem_calloc(str_len(((t_env *)node->data)->key) +
		str_len(((t_env *)node->data)->def) + 2);
		if (!envp[i])
			utils_exit(EXIT_FAILURE, "memory allocation error");
		sprintf(envp[i], "%s=%s", ((t_env *)node->data)->key,
		((t_env *)node->data)->def);
		node = node->next;
		i++;
	}
	return (envp);
}
