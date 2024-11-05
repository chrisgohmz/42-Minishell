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
	char			*new_envp[ENV_MAX_VARS];
	t_syntax_tree	*stree;

	if (!make_new_envp(new_envp, envp))
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
			free(line);
			continue ;
		}
		if (!create_syntax_tree(&stree, line))
		{
			free(line);
			free_2d_static_arr(new_envp);
			exit(EXIT_FAILURE);
		}
		free(line);
		if (!parse_tree(stree, new_envp))
		{
			free_syntax_tree(stree);
			free_2d_static_arr(new_envp);
			exit(EXIT_FAILURE);
		}
		free_syntax_tree(stree);
	}
	rl_clear_history();
	free_2d_static_arr(new_envp);
}
