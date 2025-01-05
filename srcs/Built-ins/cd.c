/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:35:53 by lpwi              #+#    #+#             */
/*   Updated: 2025/01/05 16:57:39 by lpwi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	cd_exit(t_ms_vars *ms_vars, int chdir_ret)
{
	if (chdir_ret < 0)
	{
		perror(ms_vars->exec_argv[1]);
		ms_vars->exit_value = EXIT_FAILURE;
	}
	else
		ms_vars->exit_value = EXIT_SUCCESS;
}

void	cd_builtin(t_ms_vars *ms_vars)
{
	int		chdir_ret;
	char	*home;

	if (!ms_vars->exec_argv[1])
	{
		home = getenv("HOME");
		if (!home)
		{
			ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
			ms_vars->exit_value = EXIT_FAILURE;
			return ;
		}
		chdir_ret = chdir(home);
	}
	else if (ms_vars->exec_argv[2])
	{
		ft_putendl_fd("cd: too many arguments", STDERR_FILENO);
		ms_vars->exit_value = EXIT_FAILURE;
		return ;
	}
	else
		chdir_ret = chdir(ms_vars->exec_argv[1]);
	cd_exit(ms_vars, chdir_ret);
}
