/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:36:34 by lpwi              #+#    #+#             */
/*   Updated: 2025/01/05 15:09:32 by lpwi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd_builtin(t_ms_vars *ms_vars)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		ms_vars->exit_value = EXIT_SUCCESS;
	}
	else
	{
		perror(getcwd(cwd, sizeof(cwd)));
		ms_vars->exit_value = EXIT_FAILURE;
	}
}
