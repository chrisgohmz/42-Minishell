/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 02:15:00 by cgoh              #+#    #+#             */
/*   Updated: 2025/01/02 21:43:15 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_delim_type_and_write_heredoc(t_ms_vars *ms_vars,
	t_token_type delim_type, int pipe_num, char *line)
{
	char	*expanded_str;

	if (delim_type == HEREDOC_DELIMITER)
	{
		expanded_str = perform_parameter_expansions(line, ms_vars);
		if (!expanded_str)
			return (perror("malloc"), free(line), 0);
		ft_putendl_fd(expanded_str, ms_vars->heredoc_fd[pipe_num][1]);
		free(expanded_str);
	}
	else
		ft_putendl_fd(line, ms_vars->heredoc_fd[pipe_num][1]);
	free(line);
	return (1);
}

static void	close_prev_heredoc_fd(t_ms_vars *ms_vars, int pipe_num)
{
	if (ms_vars->heredoc_fd[pipe_num][0] > -1)
		close(ms_vars->heredoc_fd[pipe_num][0]);
	if (ms_vars->heredoc_fd[pipe_num][1] > -1)
		close(ms_vars->heredoc_fd[pipe_num][1]);
}

int	perform_heredoc(char *delimiter, t_ms_vars *ms_vars,
	t_token_type delim_type, int pipe_num)
{
	char	*line;

	close_prev_heredoc_fd(ms_vars, pipe_num);
	if (pipe(ms_vars->heredoc_fd[pipe_num]) < 0)
		return (perror("pipe"), 0);
	signal(SIGINT, heredoc_sigint_handler);
	while (1)
	{
		line = readline("\001\e[1;96m\002heredoc> \001\e[0m\002");
		if (!line || !ft_strncmp(delimiter, line, ft_strlen(delimiter) + 1)
			|| g_sigint)
		{
			free(line);
			break ;
		}
		if (!check_delim_type_and_write_heredoc(ms_vars, delim_type, pipe_num,
				line))
			return (0);
	}
	close(ms_vars->heredoc_fd[pipe_num][1]);
	if (g_sigint)
		ms_vars->exit_value = 128 + SIGINT;
	return (!g_sigint);
}

int	open_heredocs(t_syntax_tree *stree, t_ms_vars *ms_vars)
{
	int	i;
	int	j;

	i = -1;
	while (++i < stree->num_branches)
	{
		j = -1;
		while (++j < stree->branches[i]->num_branches)
		{
			if (stree->branches[i]->branches[j]->type == HEREDOC_DELIMITER
				|| stree->branches[i]->branches[j]->type
				== HEREDOC_QUOTED_DELIMITER)
			{
				if (!perform_heredoc(stree->branches[i]->branches[j]->value,
						ms_vars, stree->branches[i]->branches[j]->type, i))
					return (0);
			}
		}
	}
	return (1);
}

void	reset_heredoc_fds(t_ms_vars *ms_vars)
{
	int	i;

	i = -1;
	while (++i < MAX_PIPES)
	{
		ms_vars->heredoc_fd[i][0] = -1;
		ms_vars->heredoc_fd[i][1] = -1;
	}
}
