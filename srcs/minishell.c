/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:44:42 by cgoh              #+#    #+#             */
/*   Updated: 2024/12/14 18:29:11 by lpwi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	g_signal;

static void	init_vars(t_ms_vars *ms_vars)
{
	char	*prompt;

	ms_vars->stree = NULL;
	ms_vars->pid_arr = NULL;
	ms_vars->exec_argv = NULL;
	ms_vars->stdout_fd = STDOUT_FILENO;
	ms_vars->stdin_fd = STDIN_FILENO;
	reset_heredoc_fds(ms_vars);
	ms_vars->pipe_number = 0;
	prompt = getcwd(ms_vars->prompt + sizeof(PROMPT_START) - 1, PATH_MAX);
	if (!prompt)
	{
		perror("getcwd");
		exit_cleanup(ms_vars);
	}
	ft_strlcat(ms_vars->prompt, PROMPT_END, sizeof(ms_vars->prompt));
}

int	main(void)
{
	t_ms_vars	ms_vars;

	ms_vars.exit_value = 0;
	ms_vars.proc_type = PARENT;
	ft_strlcpy(ms_vars.prompt, PROMPT_START, sizeof(ms_vars.prompt));
	if (!make_new_envp(&ms_vars))
		exit(EXIT_FAILURE);
	rl_event_hook = rl_event_handler;
	while (true)
	{
		minishell_signals();
		init_vars(&ms_vars);
		ms_vars.line = readline(ms_vars.prompt);
		if (g_signal)
			ms_vars.exit_value = 128 + SIGINT;
		if (!ms_vars.line) //handles ctrl D but after successful pipe, shell exit here. likely parent fd stdin and out is closed??
			break ;
		if (!ms_vars.line[0])
		{
			free(ms_vars.line);
			continue ;
		}
		add_history(ms_vars.line);
		if (check_syntax_and_transform_line(ms_vars.line))
		{
			ms_vars.exit_value = SYNTAX_ERROR;
			free(ms_vars.line);
			continue ;
		}
		ms_vars.stree = create_logical_branches(ms_vars.stree, ms_vars.line);
		if (!ms_vars.stree)
		{
			ms_vars.exit_value = EXIT_FAILURE;
			exit_cleanup(&ms_vars);
		}
		parse_tree(ms_vars.stree, &ms_vars);
		free_syntax_tree(ms_vars.stree);
	}
	exit_cleanup(&ms_vars);
}
