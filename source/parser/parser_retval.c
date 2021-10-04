#include "msh.h"
#include "carbon.h"
#include <stdio.h>

static int	*get_retval(void)
{
	static int	retval = 0;

	return (&retval);
}

void	msh_parser_set_retval(int retval)
{
	t_bytearray	ba;

	ba.integer = retval;
	*get_retval() = ba.byte[1];
}

int		msh_parser_get_retval(void)
{
	return (*get_retval());
}