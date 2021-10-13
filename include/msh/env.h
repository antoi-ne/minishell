/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:52:05 by alpeliss          #+#    #+#             */
/*   Updated: 2021/10/13 15:52:06 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stddef.h>
# include "carbon/llst.h"

typedef struct s_env
{
	char		*key;
	char		*def;
}				t_env;

void	msh_env_init(char **envp);

char	**msh_env_all(void);

t_env	*msh_env_get(char *key);

void	msh_env_set(char *key, char*def);

int		msh_env_unset(char *key);

void	msh_env_free(t_env *env);

t_llst	**msh_env_var(void);

#endif
