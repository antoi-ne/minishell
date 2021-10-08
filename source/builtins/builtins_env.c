#include "msh.h"

extern volatile t_globalstate	g_state;

int	msh_builtins_env(t_prog *prog)
{
	t_llst	*l;

	prog->input = prog->input;
	l = g_state.env;
	while (l)
	{
		if (((t_env *)l->data)->def)
		{
			write(1, ((t_env *)l->data)->key,
				str_len(((t_env *)l->data)->key));
			write(1, "=", 2);
			write(1, ((t_env *)l->data)->def,
				str_len(((t_env *)l->data)->def));
			write(1, "\n", 1);
		}
		l = l->next;
	}
	return (0);
}
