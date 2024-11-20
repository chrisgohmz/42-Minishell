/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:36:05 by lpwi              #+#    #+#             */
/*   Updated: 2024/11/19 19:29:37 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/** echo **/
/* outputs the args separated by spaces, terminated with newline.
   if successful, return status is 0.
   if write error, return status is non 0.
   -n flag suppresses the newline */


/*
echo by itself segfaults.
echo -n word still prints the extra -n
*/
void	echo_builtin(t_ms_vars *ms_vars)
{
	int	n_flag;
	int	j;

	n_flag = 0;
	j = 1;
	if(ft_strncmp(ms_vars->exec_argv[1], "-n", 3) == 0)
		n_flag = 1;
	while(ms_vars->exec_argv[j])
	{
		ft_putstr_fd(ms_vars->exec_argv[j], ms_vars->fd_out);
		if(ms_vars->exec_argv[j + 1])
			ft_putchar_fd(' ', ms_vars->fd_out);
		j++;
	}
	if (n_flag == 0)
		ft_putchar_fd('\n', ms_vars->fd_out);
	ms_vars->exit_value = EXIT_SUCCESS;
}
