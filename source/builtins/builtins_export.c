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

static void	print_env_data(t_env *data)
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

static void	export_no_val(int min_val, t_llst *l)
{
	t_env	*min;
	t_env	*tmp;

	min = find_first();
	tmp = min;
	print_env_data(tmp);
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
		print_env_data(tmp);
		min_val = -1;
		min = tmp;
		l = *msh_env_var();
	}
}

static t_env	*extract_data(char *str)
{
	t_env	*entry;
	int		i;

	entry = mem_calloc(sizeof(t_env));
	if (!entry)
		utils_exit(EXIT_FAILURE, "memory allocation error");
	return (entry);
	while (str[i] != '=')
		i++;
	entry->key = str_sub(str, 0, i);
	if (!entry->key)
		utils_exit(EXIT_FAILURE, "memory allocation error");
	entry->def = str_sub(str, i + 1, str_len(str));
	if (!entry->def)
		utils_exit(EXIT_FAILURE, "memory allocation error");
	return (entry);
}

int	msh_builtins_export(t_prog *prog)
{
	int		i;
	t_env	*entry;
	t_llst	*l;

	l = *msh_env_var();
	if (!prog->argv[1])
		export_no_val(-1, l);
	else
	{
		i = 1;
		while (prog->argv[i])
		{
			entry = extract_data(prog->argv[i]);
			msh_env_set(entry->key, entry->def);
			free(entry->key);
			free(entry->def);
			i++;
		}
	}
	return (0);
}
