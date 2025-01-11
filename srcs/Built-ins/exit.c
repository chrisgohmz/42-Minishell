/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:36:22 by lpwi              #+#    #+#             */
/*   Updated: 2025/01/05 15:16:31 by lpwi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	non_numeric_string(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (1);
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	check_value(char *str)
{
	int		i;
	size_t	len;
	int		sign;

	i = 0;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	len = ft_strlen(&str[i]);
	if (len > sizeof(LONG_MAX_STR) - 1)
		return (1);
	else if (len == sizeof(LONG_MAX_STR) - 1)
	{
		if (sign == 1 && ft_strncmp(&str[i], LONG_MAX_STR, len) > 0)
			return (1);
		else if (sign == -1 && ft_strncmp(&str[i], LONG_MIN_STR, len) > 0)
			return (1);
	}
	return (0);
}

void	exit_builtin(t_ms_vars *ms_vars)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	if (ms_vars->exec_argv[1])
	{
		if (non_numeric_string(ms_vars->exec_argv[1]) == 1)
		{
			ms_vars->exit_value = 2;
			ft_putendl_fd("exit: numeric argument required", STDERR_FILENO);
			exit_cleanup(ms_vars);
			return ;
		}
		else if (ms_vars->exec_argv[2])
		{
			ms_vars->exit_value = 1;
			ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
			return ;
		}
		if (check_value(ms_vars->exec_argv[1]) == 1)
		{
			ms_vars->exit_value = 2;
			ft_putendl_fd("exit: numeric argument required", STDERR_FILENO);
		}
		else
			ms_vars->exit_value = ft_atoi(ms_vars->exec_argv[1]);
	}
	exit_cleanup(ms_vars);
}
