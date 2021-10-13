/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:51:39 by alpeliss          #+#    #+#             */
/*   Updated: 2021/10/13 15:51:42 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_H
# define MSH_H

# define MSH_PROMPT "msh$ "

# include "msh/utils.h"

# include "msh/env.h"

# include "msh/reader.h"

# include "msh/parser.h"

# include "msh/builtins.h"

# include "msh/engine.h"

typedef struct s_globalstate
{
	int		running_subprocess;
	t_llst	*env;
}	t_globalstate;

#endif
