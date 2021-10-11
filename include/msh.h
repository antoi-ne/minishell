#ifndef MSH_H
# define MSH_H

# define MSH_PROMPT "msh$ "

# include "msh/utils.h"

# include "msh/env.h"

# include "msh/reader.h"

# include "msh/parser.h"

# include "msh/builtins.h"

# include "msh/engine.h"

typedef struct s_globalstate
{
	int		running_subprocess;
	t_llst	*env;
}	t_globalstate;

#endif
