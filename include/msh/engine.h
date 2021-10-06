#ifndef ENGINE_H
# define ENGINE_H

# include "carbon.h"

char	*msh_check_path(char *cmd, size_t i);
void	execute_all_progs(t_llst **prgs);
void	msh_engine_execute(t_llst **progs);

#endif
