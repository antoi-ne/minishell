#include "msh.h"
#include <stdio.h>

extern volatile t_globalstate	g_state;

static t_env	*find_first(void)
{
	t_env	*first;
	int		val;
	t_llst	*l;

	l = g_state.env;
	first = l->data;
	while (l)
	{
		val = str_cmp(((t_env *)l->data)->key, first->key);
		if (val < 0)
			first = l->data;
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
		l = g_state.env;
	}
}

static int	extract_data(char *str, t_env *entry)
{
	int		i;
	char	*def;

	i = 0;
	while (str[i] && (str[i] != '=' && str[i] != '+'))
		i++;
	if (str[i] == '\0')
		return (1);
	if (i == 0 || (str[i] == '+' && str[i + 1] != '='))
		return (printf("msh: export: %s: not a valid identifier\n", str));
	entry->key = str_sub(str, 0, i);
	if (!entry->key)
		utils_exit(EXIT_FAILURE, NULL);
	def = str_sub(str, i + 1 + (str[i] == '+'), str_len(str));
	if (!def)
		utils_exit(EXIT_FAILURE, NULL);
	if (str[i] == '+')
		entry->def = str_join(msh_env_get(entry->key)->def, def);
	else
		entry->def = str_dup(def);
	free(def);
	if (!entry->def)
		utils_exit(EXIT_FAILURE, NULL);
	return (0);
}

int	msh_builtins_export(t_prog *prog)
{
	int		i;
	t_env	entry;
	t_llst	*l;

	l = g_state.env;
	if (!prog->argv[1])
		export_no_val(-1, l);
	else
	{
		i = 1;
		while (prog->argv[i])
		{
			if (extract_data(prog->argv[i], &entry))
			{
				i++;
				continue ;
			}
			msh_env_set(entry.key, entry.def);
			free(entry.key);
			free(entry.def);
			i++;
		}
	}
	return (0);
}
