/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:44:57 by cgoh              #+#    #+#             */
/*   Updated: 2025/01/04 18:15:55 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	prepare_cmd_handling(t_syntax_tree *stree, t_ms_vars *ms_vars)
{
	if (stree->num_branches > MAX_PIPES)
	{
		ft_dprintf(STDERR_FILENO, "Error: exceeded maximum"
			" pipe count of %d\n", MAX_PIPES);
		ms_vars->exit_value = SYNTAX_ERROR;
		return ;
	}
	if (!open_heredocs(stree, ms_vars))
		return (close_heredoc_fds(ms_vars));
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	ms_vars->argv_index = 0;
	if (stree->num_branches > 1)
		handle_piped_commands(stree, ms_vars);
	else
		handle_single_command(stree, ms_vars);
}

void	parse_tree(t_syntax_tree *stree, t_ms_vars *ms_vars)
{
	int	branch;

	branch = 0;
	while (!g_sigint && branch < stree->num_branches)
	{
		if (stree->branches[branch]->type == AND
			&& ms_vars->exit_value != EXIT_SUCCESS)
			branch += 2;
		else if (stree->branches[branch]->type == OR
			&& ms_vars->exit_value == EXIT_SUCCESS)
			branch += 2;
		else if (stree->type == PIPE)
		{
			prepare_cmd_handling(stree, ms_vars);
			return ;
		}
		else
			parse_tree(stree->branches[branch++], ms_vars);
	}
}
