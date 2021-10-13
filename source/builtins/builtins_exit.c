/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancoulon <ancoulon@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:53:43 by alpeliss          #+#    #+#             */
/*   Updated: 2021/10/13 16:09:09 by ancoulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "carbon.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>

extern t_globalstate	g_state;

int	msh_builtins_exit_nofork(t_prog *prog)
{
	if (prog->argv[1])
	{
		if (!utils_is_number(prog->argv[1]))
		{
			fmt_fprint(2, "msh: exit: ");
			fmt_fprint(2, prog->argv[1]);
			fmt_fprint(2, ": numeric argument required\n");
			rl_clear_history();
			printf("exit\n");
			exit(255);
		}
		else if (prog->argv[2])
		{
			utils_printerror("exit", "too many arguments");
			return (1);
		}
		rl_clear_history();
		printf("exit\n");
		exit(types_str2int(prog->argv[1]));
	}
	rl_clear_history();
	llst_destroyl(&g_state.env, (void(*)(void *))&msh_env_free);
	printf("exit\n");
	exit(EXIT_SUCCESS);
}

int	msh_builtins_exit(t_prog *prog)
{
	if (prog->argv[1])
	{
		if (!utils_is_number(prog->argv[1]))
		{
			fmt_fprint(2, "msh: exit: ");
			fmt_fprint(2, prog->argv[1]);
			fmt_fprint(2, ": numeric argument required\n");
			exit(255);
		}
		else if (prog->argv[2])
		{
			utils_printerror("exit", "too many arguments");
			return (1);
		}
		rl_clear_history();
		exit(types_str2int(prog->argv[1]));
	}
	exit(EXIT_SUCCESS);
}
