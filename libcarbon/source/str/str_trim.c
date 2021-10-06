/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_trim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancoulon <ancoulon@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 12:50:58 by ancoulon          #+#    #+#             */
/*   Updated: 2021/10/07 00:37:07 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "carbon/str.h"

static size_t	strinc(char c, char const *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

char	*str_trim(char *str, char *set)
{
	size_t	len;
	long	start;
	long	end;

	if (!str)
		return (NULL);
	start = 0;
	while (str[start] && strinc(str[start], set))
		start++;
	end = str_len(str) - 1;
	while (end >= 0 && strinc(str[end], set))
		end--;
	if (end >= start)
		len = end - start;
	else
		len = 0;
	return (str_sub(str, start, len + 1));
}
