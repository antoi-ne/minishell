#include "msh.h"
#include "carbon.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static char *build_cmd(char *path, char *cmd)
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

char	*msh_check_path(char *cmd)
{
	t_env		*env_path;
	char		**paths;
	size_t		i;
	char		*path;
	struct stat	buf;

	if (cmd[0] == '/' || cmd[0] == '.' || cmd[0] == '~')
	{
		path = str_dup(cmd);
		if (path == NULL)
			utils_exit(EXIT_FAILURE, NULL);
		return (path);
	}
	env_path = msh_env_get("PATH");
	if (env_path == NULL)
		return (NULL);
	paths = str_split(env_path->def, ':');
	if (paths == NULL)
		utils_exit(EXIT_FAILURE, NULL);
	i = 0;
	while (paths[i])
	{
		path = build_cmd(paths[i], cmd);
		if (stat(path, &buf) == 0)
		{
			str_split_free(paths);
			return (path);
		}
		free(path);
		i++;
	}
	str_split_free(paths);
	return (NULL);
}
