/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:35:53 by lpwi              #+#    #+#             */
/*   Updated: 2024/11/17 21:29:02 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/** cd **/
/* go to the defined directory.
   absolute path: start with the root directory and provide the full path or directory
   relative path: path to a file or directory that is relative to the current directory */

/*
Handle multiple arguments to cd.
Handle no arguments to cd.
*/
void	cd_builtin(t_ms_vars *ms_vars)
{
	int	chdir_ret;

	chdir_ret = chdir(ms_vars->exec_argv[1]);
	if (chdir_ret < 0)
	{
		perror(ms_vars->exec_argv[1]);
		ms_vars->exit_value = EXIT_FAILURE;
	}
	else
		ms_vars->exit_value = EXIT_SUCCESS;
}
