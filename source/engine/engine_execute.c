/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:54:47 by alpeliss          #+#    #+#             */
/*   Updated: 2021/10/13 15:55:52 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "carbon.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <signal.h>

static void	execute_builtin_nofork(t_prog *prog)
{
	int		(*def)(t_prog *prog);
	int		ret;

	if (dup2(prog->input, STDIN_FILENO) < 0
		|| dup2(prog->output, STDOUT_FILENO) < 0)
		exit(EXIT_FAILURE);
	def = msh_builtins_get(prog->argv[0]);
	if (def == &msh_builtins_exit)
		ret = msh_builtins_exit_nofork(prog);
	else
		ret = def(prog);
	if (dup2(STDIN_FILENO, STDIN_FILENO) < 0
		|| dup2(STDIN_FILENO, STDOUT_FILENO) < 0)
		exit(EXIT_FAILURE);
	msh_parser_set_retval(ret);
}

void	msh_engine_execute(t_llst **progs)
{
	t_prog	*prog;

	if (llst_len(*progs) == 1)
	{
		prog = (t_prog *)(*progs)->data;
		if (msh_builtins_get(prog->argv[0]))
		{
			execute_builtin_nofork(prog);
			return ;
		}
	}
	execute_all_progs(progs);
}
