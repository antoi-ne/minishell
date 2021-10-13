/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:53:13 by alpeliss          #+#    #+#             */
/*   Updated: 2021/10/13 15:53:14 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

extern volatile t_globalstate	g_state;

int	msh_builtins_env(t_prog *prog)
{
	t_llst	*l;

	prog->input = prog->input;
	l = g_state.env;
	while (l)
	{
		if (((t_env *)l->data)->def)
		{
			write(1, ((t_env *)l->data)->key,
				str_len(((t_env *)l->data)->key));
			write(1, "=", 2);
			write(1, ((t_env *)l->data)->def,
				str_len(((t_env *)l->data)->def));
			write(1, "\n", 1);
		}
		l = l->next;
	}
	return (0);
}
