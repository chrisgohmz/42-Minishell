/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 20:10:18 by cgoh              #+#    #+#             */
/*   Updated: 2024/11/20 01:24:52 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_fds(t_ms_vars *ms_vars)
{
	if (ms_vars->fd_in != STDIN_FILENO)
		close(ms_vars->fd_in);
	if (ms_vars->fd_out != STDOUT_FILENO)
		close(ms_vars->fd_out);
}

void	error_cleanup(t_ms_vars *ms_vars)
{
	free_syntax_tree(ms_vars->stree);
	free(ms_vars->line);
	free_2d_malloc_array(&ms_vars->exec_argv);
	free_2d_malloc_array(&ms_vars->ep);
	free(ms_vars->pid_arr);
	close_fds(ms_vars);
	rl_clear_history();
	exit(EXIT_FAILURE);
}
