#include "msh.h"
#include "carbon.h"

int	(*msh_builtins_get(char *name))(t_prog *prog)
{
	static char	*names[2] = {"exit", NULL};
	static int	(*defs[2])(t_prog *prog) = {&msh_builtins_exit, NULL};
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
