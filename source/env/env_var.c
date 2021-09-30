#include "msh.h"
#include "carbon.h"

t_llst	**msh_env_var(void)
{
	static t_llst *var = NULL;

	return (&var);
}
