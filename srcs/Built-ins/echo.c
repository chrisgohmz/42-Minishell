/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:36:05 by lpwi              #+#    #+#             */
/*   Updated: 2024/12/01 00:26:51 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/** echo **/
/* outputs the args separated by spaces, terminated with newline.
   if successful, return status is 0.
   if write error, return status is non 0.
   -n flag suppresses the newline */

void	echo_builtin(t_ms_vars *ms_vars)
{
	int	n_flag;
	int	j;

	n_flag = 0;
	j = 1;
	if(ms_vars->exec_argv[1])
	{
		if(ft_strncmp(ms_vars->exec_argv[1], "-n", 3) == 0)
		{
			n_flag = 1;
			j++;
		}
		while(ms_vars->exec_argv[j])
		{
			ft_putstr_fd(ms_vars->exec_argv[j], STDOUT_FILENO);
			if(ms_vars->exec_argv[j + 1])
				ft_putchar_fd(' ', STDOUT_FILENO);
			j++;
		}
	}
	if (n_flag == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	ms_vars->exit_value = EXIT_SUCCESS;
}
