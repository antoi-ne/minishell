/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_retval.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:58:33 by alpeliss          #+#    #+#             */
/*   Updated: 2021/10/13 15:58:36 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	*get_retval() = retval;
}

int	msh_parser_get_retval(void)
{
	return (*get_retval());
}
