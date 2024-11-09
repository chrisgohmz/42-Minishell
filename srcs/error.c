/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 20:10:18 by cgoh              #+#    #+#             */
/*   Updated: 2024/11/09 18:07:52 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error_cleanup(t_ms_vars *ms_vars)
{
	int	i;

	i = 0;
	while (ms_vars->exec_argv[i])
		free(ms_vars->exec_argv[i++]);
	free_syntax_tree(ms_vars->stree);
	free(ms_vars->line);
	free_2d_static_arr(ms_vars->new_envp);
	rl_clear_history();
	exit(EXIT_FAILURE);
}
