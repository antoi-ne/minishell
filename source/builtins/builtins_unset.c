/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:54:03 by alpeliss          #+#    #+#             */
/*   Updated: 2021/10/13 15:54:04 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	msh_builtins_unset(t_prog *prog)
{
	int	i;

	i = 1;
	while (prog->argv[i])
	{
		if (msh_env_get(prog->argv[i]))
			msh_env_unset(prog->argv[i]);
		i++;
	}
	return (0);
}
