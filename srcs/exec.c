/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 10:54:16 by cgoh              #+#    #+#             */
/*   Updated: 2024/12/09 19:16:42 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
cgoh: Good start! Now I need u to modify it such that it searches $PATH, not just /usr/bin/.
Handle command when given absolute/relative path (e.g. /usr/bin/cat, ./minishell).
exit status may also not be 127 on failure, see https://www.gnu.org/software/bash/manual/bash.html#Exit-Status.
may want to look into access() function.
*/

static void	exec_cmd_not_found_handler(t_ms_vars *ms_vars)
{
	char	*handler_path;
	char	**arr;

	handler_path = "/lib/command-not-found";
	arr = ft_calloc(3, sizeof(char *));
	if (!arr)
		return ;
	arr[0] = handler_path;
	arr[1] = ms_vars->exec_argv[0];
	execve(handler_path, arr, ms_vars->ep);
	free(arr);
	errno = ENOENT;
	perror(ms_vars->exec_argv[0]);
}

static char **store_path(void)
{
	char *path;
	char **bin;

	path = getenv("PATH");
	if (!path)
		return NULL;
	bin  = ft_split(path, ':');
	if (!bin)
	{
		perror("split failure\n");
		return (NULL);
	}
	return (bin);
}

static void relative_path(t_ms_vars *ms_vars, struct stat *statbuf)
{
	int i;
	char **bin;
	char *path;
	char **path_and_cmd;

	i = 0;
	bin = store_path();
	if (!bin)
	{
		errno = ENOENT;
		perror(ms_vars->exec_argv[0]);
		ms_vars->exit_value = 127;
		return ;
	}
	path = NULL;
	while (bin[i] && ms_vars->exec_argv[0][0])
	{
		path_and_cmd = malloc(sizeof(char *) * 3);
		if(!path_and_cmd)
			return ;
		path_and_cmd[0] = ft_strdup(bin[i]);
		path_and_cmd[1] = ft_strdup(ms_vars->exec_argv[0]);
		path_and_cmd[2] = NULL;
		path = ft_multi_strjoin(2, path_and_cmd, "/");
		if(access(path, F_OK) != -1)
		{
			if (stat(path, statbuf) < 0)
				perror("stat");
			if (S_ISDIR(statbuf->st_mode))
			{
				ft_dprintf(STDERR_FILENO, "%s: Is a directory\n", ms_vars->exec_argv[0]);
				ms_vars->exit_value = 126;
				free_2d_arr((void***)&path_and_cmd);
				free_2d_arr((void***)&bin);
				free(path);
				return ;
			}
			if (access(path, X_OK) == -1)
			{
				perror(ms_vars->exec_argv[0]);
				ms_vars->exit_value = 126;
				free_2d_arr((void***)&path_and_cmd);
				free_2d_arr((void***)&bin);
				free(path);
				return ;
			}
			else
				break;
		}
		free_2d_arr((void***)&path_and_cmd);
		free(path);
		path = NULL;
		i++;
	}
	if (!path)
		exec_cmd_not_found_handler(ms_vars);
	if(path && execve(path, ms_vars->exec_argv, ms_vars->ep) == -1)
		perror(ms_vars->exec_argv[0]);
	ms_vars->exit_value = 127;
	free_2d_arr((void***)&bin);
	free_2d_arr((void***)&path_and_cmd);
	free(path);
}

void	exec_cmd(t_ms_vars *ms_vars)
{	
	struct stat	statbuf;

	if (ms_vars->stdout_fd != STDOUT_FILENO)
		close(ms_vars->stdout_fd); //For the case of single execve cmd, close the saved stdout fd from earlier, refer to redirections.c lines 19-24
	if (ms_vars->stdin_fd != STDIN_FILENO)
		close(ms_vars->stdin_fd); //likewise for stdin
	if(ft_strchr(ms_vars->exec_argv[0], '/'))
	{
		if (access(ms_vars->exec_argv[0], F_OK) != -1)
		{
			if (stat(ms_vars->exec_argv[0], &statbuf) < 0)
				perror("stat");
			if (S_ISDIR(statbuf.st_mode))
			{
				ft_dprintf(STDERR_FILENO, "%s: Is a directory\n", ms_vars->exec_argv[0]);
				ms_vars->exit_value = 126;
				return ;
			}
		}
		if(execve(ms_vars->exec_argv[0], ms_vars->exec_argv, ms_vars->ep) == -1)
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
