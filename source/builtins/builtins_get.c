#include "msh.h"
#include "carbon.h"

static void	to_lowercase(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 'a' - 'A';
		i++;
	}
}

int	(*msh_builtins_get(char *name))(t_prog *prog)
{
	char	*lc;

	static char	*names[8] = {"echo", "cd", "pwd", "export", "unset", "env"
		, "exit", NULL};
	static int	(*defs[8])(t_prog *prog) = {&msh_builtins_echo
		, &msh_builtins_cd, &msh_builtins_pwd, &msh_builtins_export
			, &msh_builtins_unset, &msh_builtins_env, &msh_builtins_exit, NULL};
	size_t		i;

	i = 0;
	lc = str_dup(name);
	if (lc == NULL)
		utils_exit(EXIT_FAILURE, NULL);
	to_lowercase(lc);
	while (names[i])
	{
		if (str_cmp(lc, names[i]) == 0)
			return (defs[i]);
		i++;
	}
	return (NULL);
}
