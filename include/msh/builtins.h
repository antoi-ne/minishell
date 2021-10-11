#ifndef BUILTINS_H
# define BUILTINS_H

# include "unistd.h"
# include "errno.h"
# include "string.h"

int	(*msh_builtins_get(char *name))(t_prog *prog);

int	msh_builtins_echo(t_prog *prog);
int	msh_builtins_cd(t_prog *prog);
int	msh_builtins_pwd(t_prog *prog);
int	msh_builtins_export(t_prog *prog);
int	msh_builtins_unset(t_prog *prog);
int	msh_builtins_env(t_prog *prog);
int	msh_builtins_exit(t_prog *prog);
int	msh_builtins_exit_nofork(t_prog *prog);

#endif
