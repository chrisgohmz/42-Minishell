/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 20:10:18 by cgoh              #+#    #+#             */
/*   Updated: 2024/12/06 04:36:46 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_cleanup(t_ms_vars *ms_vars)
{
	free_syntax_tree(ms_vars->stree);
	free_2d_arr((void ***)&ms_vars->exec_argv);
	free_2d_arr((void ***)&ms_vars->ep);
	free(ms_vars->pid_arr);
	rl_clear_history();
	if (ms_vars->stdin_fd != STDIN_FILENO)
		close(ms_vars->stdin_fd);
	if (ms_vars->stdout_fd != STDOUT_FILENO)
		close(ms_vars->stdout_fd);
	exit(ms_vars->exit_value);
}
