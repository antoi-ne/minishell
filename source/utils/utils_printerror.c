/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_printerror.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:59:36 by alpeliss          #+#    #+#             */
/*   Updated: 2021/10/13 15:59:37 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int	utils_printerror(char *prog, char *msg)
{
	if (prog)
		printf("msh: %s: %s\n", prog, msg);
	else
		printf("msh: %s\n", msg);
	return (1);
}
