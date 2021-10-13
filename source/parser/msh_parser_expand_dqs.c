/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parser_expand_dqs.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:57:39 by alpeliss          #+#    #+#             */
/*   Updated: 2021/10/13 15:57:40 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static char	*dqs_newstr(char *str, char *expanded, size_t start, size_t end)
{
	size_t	i;
	size_t	j;
	char	*new;

	i = -1;
	new = mem_calloc(sizeof(char)
			* (str_len(str) - (end - start) + str_len(expanded) + 1));
	if (new == NULL)
		utils_exit(EXIT_FAILURE, NULL);
	while (++i < start)
		new[i] = str[i];
	j = -1;
	while (++j < str_len(expanded))
	{
		new[i] = expanded[j];
		i++;
	}
	j = end;
	while (str[j])
	{
		new[i] = str[j];
		i++;
		j++;
	}
	return (new);
}

static char	*find_expanded(t_env *var)
{
	char	*str;

	if (var == NULL)
		return (str_dup(""));
	str = str_dup(var->def);
	if (str == NULL)
		utils_exit(EXIT_FAILURE, NULL);
	return (str);
}

static t_env	*get_var(char *str, int i, int j)
{
	char	*vn;
	t_env	*var;

	vn = str_sub(str, i, j);
	var = msh_env_get(vn);
	free(vn);
	return (var);
}

char	*msh_parser_expand_dqs(char *str, size_t i, size_t start)
{
	t_env	*var;
	char	*expanded;
	char	*new;

	while (str[i])
	{
		if (str[i] == '$')
		{
			start = i;
			i++;
			while (str[i] && str[i] != ' ' && str[i] != '$')
				i++;
			if (i - start < 2)
				continue ;
			var = get_var(str, start + 1, i - start - 1);
			expanded = find_expanded(var);
			new = dqs_newstr(str, expanded, start, i);
			free(str);
			str = new;
			i = start + str_len(expanded) - 1;
			free(expanded);
		}
		i++;
	}
	return (str);
}
