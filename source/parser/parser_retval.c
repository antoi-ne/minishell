#include "msh.h"
#include "carbon.h"

static int	*get_retval(void)
{
	static int	retval = 0;

	return (&retval);
}

void	msh_parser_set_retval(int retval)
{
	*get_retval() = retval;
}

int		msh_parser_get_retval(void)
{
	return (*get_retval());
}