/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llst_push.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancoulon <ancoulon@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 11:30:20 by ancoulon          #+#    #+#             */
/*   Updated: 2021/09/20 16:15:22 by ancoulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "carbon/llst.h"

void	llst_push(t_llst **lst, t_llst *node)
{
	if (!lst)
		return ;
	if (!*lst)
		*lst = node;
	else
	{
		llst_tail(*lst)->next = node;
	}
}
