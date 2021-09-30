#include "msh.h"

int	msh_builtins_pwd(t_prog *pr)
{
	char	*str;

	str = getcwd(NULL, 0);
	write(1, str, str_len(str));
	write(1, "\n", 1);
	free(str);
	return (0);
}
