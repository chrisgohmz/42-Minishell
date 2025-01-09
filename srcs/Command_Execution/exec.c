/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 10:54:16 by cgoh              #+#    #+#             */
/*   Updated: 2025/01/05 18:04:09 by lpwi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**store_path(t_ms_vars *ms_vars)
{
	char	*path;
	char	**bin;

	path = getenv("PATH");
	if (!path)
	{
		errno = ENOENT;
		perror(ms_vars->exec_argv[0]);
		ms_vars->exit_value = 127;
		return (NULL);
	}
	bin = ft_split(path, ':');
	if (!bin)
	{
		perror("split failure\n");
		errno = ENOENT;
		perror(ms_vars->exec_argv[0]);
		ms_vars->exit_value = 127;
		return (NULL);
	}
	return (bin);
}

static char	*get_path(char *bin, char *cmd)
{
	char	**path_and_cmd;
	char	*path;

	path_and_cmd = malloc(sizeof(char *) * 3);
	if (!path_and_cmd)
		return (NULL);
	path_and_cmd[0] = ft_strdup(bin);
	path_and_cmd[1] = ft_strdup(cmd);
	path_and_cmd[2] = NULL;
	path = ft_multi_strjoin(2, path_and_cmd, "/");
	free_2d_arr((void ***)&path_and_cmd);
	return (path);
}

static void	relative_path_2(t_ms_vars *ms_vars, char *path)
{
	if (!path)
		exec_cmd_not_found_handler(ms_vars);
	if (path && execve(path, ms_vars->exec_argv, ms_vars->ep) == -1)
		perror(ms_vars->exec_argv[0]);
	ms_vars->exit_value = 127;
}

static void	relative_path(t_ms_vars *ms_vars, struct stat *statbuf)
{
	int		i;
	int		access_res;
	char	**bin;
	char	*path;

	i = 0;
	bin = store_path(ms_vars);
	if (!bin)
		return ;
	path = NULL;
	while (bin[i] && ms_vars->exec_argv[0][0])
	{
		path = get_path(bin[i++], ms_vars->exec_argv[0]);
		access_res = rel_check_access(ms_vars, statbuf, path, bin);
		if (access_res == 0)
			break ;
		else if (access_res == -1)
			return ;
		free(path);
		path = NULL;
	}
	relative_path_2(ms_vars, path);
	free_all(bin, path);
}

void	exec_cmd(t_ms_vars *ms_vars)
{
	struct stat	statbuf;

	if (ms_vars->stdout_fd != STDOUT_FILENO)
		close(ms_vars->stdout_fd);
	if (ms_vars->stdin_fd != STDIN_FILENO)
		close(ms_vars->stdin_fd);
	if (ft_strchr(ms_vars->exec_argv[0], '/'))
	{
		if (abs_check_access(ms_vars, &statbuf) == -1)
			return ;
		if (execve(ms_vars->exec_argv[0],
				ms_vars->exec_argv, ms_vars->ep) == -1)
		{
			perror(ms_vars->exec_argv[0]);
			if (errno == EACCES)
				ms_vars->exit_value = 126;
			else
				ms_vars->exit_value = 127;
		}
		return ;
	}
	else
		relative_path(ms_vars, &statbuf);
}
