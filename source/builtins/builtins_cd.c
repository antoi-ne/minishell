#include "msh.h"

static void	change_directory_env(void)
{
	t_env	*old_pwd;
	t_env	*pwd;

	old_pwd = msh_env_get("OLDPWD");
	pwd = msh_env_get("PWD");
	if (old_pwd)
		old_pwd->def = pwd->def;
	if (pwd)
	{
		free(pwd->def);
		pwd->def = getcwd(NULL, 0);
	}
}

int	msh_builtins_cd(t_prog *prog)
{
	int		i;
	t_env	*home;

	i = 0;
	if (!prog->argv[1])
	{
		home = msh_env_get("HOME");
		if (home)
			i = chdir(home->def);
		else
			write(1, "bash: cd: HOME not set\n", 23);
	}
	else
		i = chdir(prog->argv[1]);
	if (i)
	{
		write(1, "bash: cd: ", 10);
		write(1, prog->argv[1], str_len(prog->argv[1]));
		write(1, ": ", 2);
		write(1, strerror(errno), str_len(strerror(errno)));
		write(1, "\n", 1);
	}
	else
		change_directory_env();
	return (1);
}
