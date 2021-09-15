/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_ncpy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancoulon <ancoulon@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 19:14:36 by ancoulon          #+#    #+#             */
/*   Updated: 2021/03/08 10:28:21 by ancoulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "carbon/str.h"

char	*str_ncpy(char *d, char *s, size_t len)
{
	size_t	i;

	if (d && s)
	{
		i = 0;
		while (s[i] && i < (len - 1))
		{
			d[i] = s[i];
			i++;
		}
		d[i] = '\0';
	}
	return (d);
}