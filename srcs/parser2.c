/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 18:38:40 by cgoh              #+#    #+#             */
/*   Updated: 2024/11/17 21:45:47 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_cmd_is_builtin(t_ms_vars *ms_vars)
{
	if (ft_strncmp(ms_vars->exec_argv[0], "cd", 3) == 0)
		return (cd_builtin(ms_vars), 1);
	else if (ft_strncmp(ms_vars->exec_argv[0], "pwd", 4) == 0)
		return (pwd_builtin(), 1);
	else if (ft_strncmp(ms_vars->exec_argv[0], "echo", 5) == 0)
		return (echo_builtin(ms_vars), 1);
	else if (ft_strncmp(ms_vars->exec_argv[0], "export", 7) == 0)
		return (export_builtin(ms_vars), 1);
	else if (ft_strncmp(ms_vars->exec_argv[0], "unset", 6) == 0)
		return (unset_builtin(ms_vars), 1);
	else if (ft_strncmp(ms_vars->exec_argv[0], "env", 4) == 0)
		return (env_builtin(), 1);
	else if (ft_strncmp(ms_vars->exec_argv[0], "exit", 5) == 0)
		return (exit_builtin(ms_vars), 1);
	return (0);
}
