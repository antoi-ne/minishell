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
			utils_exit(EXIT_FAILURE, "memory allocation error");
		full_path = str_join(tmp, cmd);
		free(tmp);
	}
	if (full_path == NULL)
		utils_exit(EXIT_FAILURE, "memory allocation error");
	return (full_path);
}

char	*msh_check_path(char *cmd)
{
	t_env		*env_path;
	char		**paths;
	size_t		i;
	char		*path;
	struct stat	buf;

	env_path = msh_env_get("PATH");
	if (env_path == NULL)
		return (NULL);
	paths = str_split(env_path->def, ':');
	if (paths == NULL)
		utils_exit(EXIT_FAILURE, "memory allocation error");
	i = 0;
	while (paths[i])
	{
		path = build_cmd(paths[i], cmd);
		if (stat(path, &buf) == 0)
			return (path);
		i++;
	}
	return (NULL);
}
