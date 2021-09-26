#ifndef BUILTINS_H
# define BUILTINS_H

int	(*msh_builtins_get(char *name))(t_prog *prog);

int	msh_builtins_exit(t_prog *prog);

#endif
