/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_get.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:53:50 by alpeliss          #+#    #+#             */
/*   Updated: 2021/10/13 15:53:51 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	char		*lc;
	static char	*names[8] = {"echo", "cd", "pwd", "export"
		, "unset", "env", "exit", NULL};
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
		{
			free (lc);
			return (defs[i]);
		}
		i++;
	}
	free(lc);
	return (NULL);
}
