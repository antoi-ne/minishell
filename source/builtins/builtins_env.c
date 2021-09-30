#include "msh.h"

int	msh_builtins_env(t_prog *prog)
{
	t_llst	*l;

	prog->input = prog->input;
	l = *msh_env_var();
	while (l)
	{
		if (((t_env *)l->data)->def)
		{
			write(1, ((t_env *)l->data)->key,
				str_len(((t_env *)l->data)->key));
			write(1, "=\"", 2);
			write(1, ((t_env *)l->data)->def,
				str_len(((t_env *)l->data)->def));
			write(1, "\"", 1);
			write(1, "\n", 1);
		}
		l = l->next;
	}
	return (0);
}
