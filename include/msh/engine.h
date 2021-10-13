/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpeliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:51:59 by alpeliss          #+#    #+#             */
/*   Updated: 2021/10/13 15:52:00 by alpeliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include "carbon.h"

char	*msh_check_path(char *cmd, size_t i);
void	execute_all_progs(t_llst **prgs);
void	msh_engine_execute(t_llst **progs);

#endif
