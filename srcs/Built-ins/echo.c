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

static int	newline_flag(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (-1);
	i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (-1);
		i++;
	}
	return (0);
}

void	echo_builtin(t_ms_vars *ms_vars)
{
	int	n_flag;
	int	i;

	n_flag = 0;
	i = 1;
	if (ms_vars->exec_argv[i] && newline_flag(ms_vars->exec_argv[i]) == 0)
	{
		n_flag = 1;
		i++;
	}
	while (ms_vars->exec_argv[i] && newline_flag(ms_vars->exec_argv[i]) == 0)
	{
		i++;
	}
	while (ms_vars->exec_argv[i])
	{
		ft_putstr_fd(ms_vars->exec_argv[i], STDOUT_FILENO);
		if (ms_vars->exec_argv[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (n_flag == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	ms_vars->exit_value = EXIT_SUCCESS;
}
