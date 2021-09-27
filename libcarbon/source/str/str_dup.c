/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_dup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancoulon <ancoulon@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 19:05:12 by ancoulon          #+#    #+#             */
/*   Updated: 2021/09/27 14:42:15 by ancoulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "carbon/str.h"

#include "carbon/mem.h"

char	*str_dup(char *s)
{
	char	*cpy;

	cpy = mem_calloc(str_len(s) + 1);
	str_cpy(cpy, s);
	return (cpy);
}
