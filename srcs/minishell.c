/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:44:42 by cgoh              #+#    #+#             */
/*   Updated: 2024/11/05 18:31:31 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	t_syntax_tree	*stree;
	t_ms_vars		ms_vars;

	ms_vars.exit_value = 0;
	if (!make_new_envp(ms_vars.new_envp, envp))
		exit(EXIT_FAILURE);
	while (1 || argc || argv)
	{
		stree = NULL;
		line = readline("Minishell$ ");
		if (!line)
			break ;
		if (!line[0])
		{
			free(line);
			continue;
		}
		add_history(line);
		if (check_syntax_and_transform_line(line))
		{
			ms_vars.exit_value = 2;
			free(line);
			continue ;
		}
		if (!create_syntax_tree(&stree, line))
		{
			ms_vars.exit_value = EXIT_FAILURE;
			free(line);
			break;
		}
		free(line);
		if (!parse_tree(stree, &ms_vars))
		{
			ms_vars.exit_value = EXIT_FAILURE;
			free_syntax_tree(stree);
			break;
		}
		free_syntax_tree(stree);
	}
	rl_clear_history();
	free_2d_static_arr(ms_vars.new_envp);
	exit(ms_vars.exit_value);
}
