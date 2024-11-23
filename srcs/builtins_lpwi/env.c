/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:36:11 by lpwi              #+#    #+#             */
/*   Updated: 2024/11/17 21:34:35 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/** env **/
/* output a list of all environment variabless.
   environment variables are dynamic values that affect the behaviour of proccesses on a system. They are available to the shell and any child processes spawned from the shell. */
void	env_builtin(t_ms_vars *ms_vars)
{
	int	i;

	i = 0;
	while(ms_vars->ep[i])
	{
		ft_putendl_fd(ms_vars->ep[i], ms_vars->fd_out);
		i++;
	}
	ms_vars->exit_value = EXIT_SUCCESS;
}
