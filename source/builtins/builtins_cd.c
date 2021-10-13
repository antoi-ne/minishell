/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:53:07 by alpeliss          #+#    #+#             */
/*   Updated: 2021/10/13 15:53:09 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include <stdio.h>

static void	change_directory_env(char *old_cwd)
{
	char	*cwd;

	msh_env_set("OLDPWD", old_cwd);
	free(old_cwd);
	cwd = getcwd(NULL, 0);
	msh_env_set("PWD", cwd);
	free(cwd);
}

int	msh_builtins_cd(t_prog *prog)
{
	int		i;
	t_env	*home;
	char	*old_cwd;

	i = 0;
	old_cwd = getcwd(NULL, 0);
	if (!prog->argv[1])
	{
		home = msh_env_get("HOME");
		if (home)
			i = chdir(home->def);
		else
			write(1, "msh: cd: HOME not set\n", 23);
	}
	else
		i = chdir(prog->argv[1]);
	if (i)
		printf("msh: cd: %s: %s\n", prog->argv[1], strerror(errno));
	else
		change_directory_env(old_cwd);
	return (1);
}
