#include "msh.h"

int	msh_builtins_unset(t_prog *prog)
{
	int	i;

	i = 1;
	while (prog->argv[i])
	{
		if (msh_env_get(prog->argv[i]))
			msh_env_unset(prog->argv[i]);
		i++;
	}
	return (0);
}