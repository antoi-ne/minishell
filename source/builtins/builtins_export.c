#include "msh.h"

static t_env	*find_first(void)
{
	t_env	*first;
	int		min_val;
	int		val;
	t_llst	*l;

	l = *msh_env_var();
	first = l->data;
	min_val = str_cmp(first->key, NULL);
	while (l)
	{
		val = str_cmp(((t_env *)l->data)->key, NULL);
		if (val < min_val)
		{
			min_val = val;
			first = l->data;
		}
		l = l->next;
	}
	return (first);
}

static void	print_env_data(t_prog pr, t_env *data)
{
	write(1, "declare -x ", 11);
	write(1, data->key, str_len(data->key));
	if (data->def)
	{
		write(1, "=\"", 2);
		write(1, data->def, str_len(data->def));
		write(1, "\"", 1);
	}
	write(1, "\n", 1);
}

static void	export_no_val(t_prog pr, int min_val, t_llst *l)
{
	t_env	*min;
	t_env	*tmp;

	min = find_first();
	tmp = min;
	print_env_data(pr, tmp);
	while (1)
	{
		while (l)
		{
			if (str_cmp(((t_env *)l->data)->key, min->key) > 0 && (min_val < 0
						|| str_cmp(((t_env *)l->data)->key, tmp->key) < 0))
			{
				tmp = l->data;
				min_val = 0;
			}
			l = l->next;
		}
		if (min_val == -1)
			return ;
		print_env_data(pr, tmp);
		min_val = -1;
		min = tmp;
		l = g_msh_env;
	}
}

int	msh_builtins_export(t_prog *prog)
{
	int		i;
	t_env	*entry;

	if (!prog->argv[1])
		export_no_val(*prog, -1, g_msh_env);
	else
	{
		i = 1;
		while (prog->argv[i])
		{
			entry = extract_data(pr.argv[i]);
			msh_env_set(entry);
			i++;
		}
	}
	return (0);
}
