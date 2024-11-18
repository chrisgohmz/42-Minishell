/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:36:22 by lpwi              #+#    #+#             */
/*   Updated: 2024/11/17 21:46:24 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/** exit **/
/* exit the current shell session.
   take no options: returns the exit status of the last command. */

/*
hint: ms_vars->exit_value.
Make sure there's no leaks, error.c gives an idea of what needs to be freed.
*/
void	exit_builtin(t_ms_vars *ms_vars)
{
	(void)ms_vars;
}
