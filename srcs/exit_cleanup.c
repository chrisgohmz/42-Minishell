/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 20:10:18 by cgoh              #+#    #+#             */
/*   Updated: 2024/12/05 01:58:50 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_2d_malloc_array(char ***split)
{
	int	i;

	if (!*split)
		return ;
	i = 0;
	while ((*split)[i])
	{
		free((*split)[i]);
		(*split)[i] = NULL;
		i++;
	}
	free(*split);
	*split = NULL;
}

void	exit_cleanup(t_ms_vars *ms_vars)
{
	free_syntax_tree(ms_vars->stree);
	free_2d_malloc_array(&ms_vars->exec_argv);
	free_2d_malloc_array(&ms_vars->ep);
	free(ms_vars->pid_arr);
	rl_clear_history();
	exit(ms_vars->exit_value);
}
