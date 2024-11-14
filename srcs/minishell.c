/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:44:42 by cgoh              #+#    #+#             */
/*   Updated: 2024/11/09 18:02:31 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	init_vars(t_ms_vars *ms_vars)
{
	char	*prompt;

	ms_vars->stree = NULL;
	ms_vars->argv_index = 0;
	ms_vars->pid_arr = NULL;
	ms_vars->exec_argv = NULL;
	prompt = getcwd(ms_vars->prompt + sizeof(PROMPT_START) - 1, PATH_MAX);
	if (!prompt)
	{
		perror("getcwd");
		error_cleanup(ms_vars);
	}
	ft_strlcat(ms_vars->prompt, PROMPT_END, sizeof(ms_vars->prompt));
}

int	main(int argc, char **argv)
{
	t_ms_vars	ms_vars;

	ms_vars.exit_value = 0;
	ft_strlcpy(ms_vars.prompt, PROMPT_START, sizeof(ms_vars.prompt));
	if (!make_new_envp(&ms_vars))
		exit(EXIT_FAILURE);
	while (1 || argc || argv)
	{
		init_vars(&ms_vars);
		ms_vars.line = readline(ms_vars.prompt);
		if (!ms_vars.line)
			break ;
		if (!ms_vars.line[0])
		{
			free(ms_vars.line);
			continue ;
		}
		add_history(ms_vars.line);
		if (check_syntax_and_transform_line(ms_vars.line))
		{
			ms_vars.exit_value = 2;
			free(ms_vars.line);
			continue ;
		}
		create_syntax_tree(&ms_vars.stree, ms_vars.line, &ms_vars);
		free(ms_vars.line);
		ms_vars.line = NULL;
		parse_tree(ms_vars.stree, &ms_vars);
		free_syntax_tree(ms_vars.stree);
		free(ms_vars.pid_arr);
	}
	rl_clear_history();
	free_2d_malloc_array(&ms_vars.ep);
	exit(ms_vars.exit_value);
}
