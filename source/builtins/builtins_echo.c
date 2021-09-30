#include "msh.h"

static int	is_option(char *str)
{
	int	i;

	if (!str)
		return (0);
	if (str[0] != '-')
		return (0);
	if (str[1] != 'n')
		return (0);
	i = 1;
	while (str[++i])
		if (str[i] != 'n')
			return (0);
	return (1);
}

int	msh_builtins_echo(t_prog *prog)
{
	int		i;
	int		opt;

	i = 1;
	opt = 1;
	while (prog->argv[i] && is_option(prog->argv[i]))
	{
		i++;
		opt = 0;
	}
	while (prog->argv[i])
	{
		write(1, prog->argv[i], str_len(prog->argv[i]));
		i++;
		if (prog->argv[i])
			write(1, " ", 1);
	}
	if (opt)
		write(1, "\n", 1);
	return (0);
}
