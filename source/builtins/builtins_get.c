#include "msh.h"
#include "carbon.h"

int	(*msh_builtins_get(char *name))(t_prog *prog)
{
	static char	*names[8] = {"echo", "cd", "pwd", "export", "unset", "env"
		, "exit", NULL};
	static int	(*defs[8])(t_prog *prog) = {&msh_builtins_echo
		, &msh_builtins_cd, &msh_builtins_pwd, &msh_builtins_export, 
			&msh_builtins_unset, &msh_builtins_env, &msh_builtins_exit, NULL};
	size_t		i;

	i = 0;
	while (names[i])
	{
		if (str_cmp(name, names[i]) == 0)
			return (defs[i]);
		i++;
	}
	return (NULL);
}
