/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:59:19 by alpeliss          #+#    #+#             */
/*   Updated: 2021/10/13 15:59:20 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int	utils_exit(int ec, char *err_msg)
{
	if (ec != EXIT_SUCCESS)
	{
		if (err_msg == NULL)
			perror("msh");
		else
			printf("msh: %s\n", err_msg);
	}
	exit(ec);
}
