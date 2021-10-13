/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_check_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:54:26 by alpeliss          #+#    #+#             */
/*   Updated: 2021/10/13 15:54:27 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "carbon.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static char	*build_cmd(char *path, char *cmd)
{
	char	*full_path;
	char	*tmp;

	if (path[str_len(path) - 1] == '/')
		full_path = str_join(path, cmd);
	else
	{
		tmp = str_join(path, "/");
		if (tmp == NULL)
			utils_exit(EXIT_FAILURE, NULL);
		full_path = str_join(tmp, cmd);
		free(tmp);
	}
	if (full_path == NULL)
		utils_exit(EXIT_FAILURE, NULL);
	return (full_path);
}

char	*absolute_path(char *cmd)
{
	char	*path;

	path = str_dup(cmd);
	if (path == NULL)
		utils_exit(EXIT_FAILURE, NULL);
	return (path);
}

char	*msh_check_path(char *cmd, size_t i)
{
	t_env		*env_path;
	char		**paths;
	char		*path;
	struct stat	buf;

	if (cmd[0] == '/' || cmd[0] == '.' || cmd[0] == '~')
		return (absolute_path(cmd));
	env_path = msh_env_get("PATH");
	if (env_path == NULL)
		return (NULL);
	paths = str_split(env_path->def, ':');
	if (paths == NULL)
		utils_exit(EXIT_FAILURE, NULL);
	while (paths[++i])
	{
		path = build_cmd(paths[i], cmd);
		if (stat(path, &buf) == 0)
		{
			str_split_free(paths);
			return (path);
		}
		free(path);
	}
	str_split_free(paths);
	return (NULL);
}
