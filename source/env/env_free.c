#include "msh.h"
#include "carbon.h"

void	msh_env_free(t_env *env)
{
	free(env->key);
	free(env->def);
	free(env);
}
