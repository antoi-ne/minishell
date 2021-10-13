/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:56:16 by alpeliss          #+#    #+#             */
/*   Updated: 2021/10/13 15:56:18 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "carbon.h"

void	msh_env_free(t_env *env)
{
	free(env->key);
	free(env->def);
	free(env);
}
