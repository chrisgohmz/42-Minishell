/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 10:54:16 by cgoh              #+#    #+#             */
/*   Updated: 2024/11/09 13:48:10 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_cmd(t_ms_vars *ms_vars)
{
	char bin[] = "/usr/bin/";
	char *path;
	int len;

	len = ft_strlen(bin) + ft_strlen(ms_vars->exec_argv[0]);
	path = malloc(sizeof(char) * (len + 1));
	if(!path)
		return ;
	ft_strlcpy(path, bin, ft_strlen(bin) + 1);
	ft_strlcat(path, ms_vars->exec_argv[0], len + 1);

	if(execve(path, ms_vars->exec_argv, ms_vars->ep) == -1)
	{
		perror("execve unsuccessful\n");
		ms_vars->exit_value = 127;
		return ;
	}
	free(path);
	ms_vars->exit_value = EXIT_SUCCESS;
}
