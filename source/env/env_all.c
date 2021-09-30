#include "msh.h"
#include "carbon.h"
#include <stdio.h>

t_llst	*g_msh_env;

char **msh_env_all(void)
{
	char	**envp;
	size_t	len;
	size_t	i;
	t_llst	*node;

	len = llst_len(*msh_env_var());
	envp = mem_calloc(sizeof(char *) * (len + 1));
	if (!envp)
		utils_exit(EXIT_FAILURE, "memory allocation error");
	i = 0;
	node = *msh_env_var();
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
