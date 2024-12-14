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

static char **store_path(void)
{
	char *path;
	char **bin;

	path = getenv("PATH");
	bin  = ft_split(path, ':');
	if (!bin)
	{
		perror("split failure\n");
		return (NULL);
	}
	return (bin);
}

static int relative_path(t_ms_vars *ms_vars)
{
	int i;
	char **bin;
	char *path;
	char **path_and_cmd;

	i = 0;
	bin = store_path();
	if (!bin)
	{
		perror("store path failure\n");
		return (0);
	}
	while (bin[i])
	{
		//cgoh: ft_multi_strjoin is probably easier.
		path_and_cmd = malloc(sizeof(char *) * 3);
		if(!path_and_cmd)
			return (1);
		path_and_cmd[0] = ft_strdup(bin[i]);
		path_and_cmd[1] = ft_strdup(ms_vars->exec_argv[0]);
		path_and_cmd[2] = NULL;
		path = ft_multi_strjoin(2, path_and_cmd, "/");
		if(access(path, F_OK | X_OK) != -1)
			break ;
		i++;
	}
	if(execve(path, ms_vars->exec_argv, ms_vars->ep) == -1)
	{
		perror(ms_vars->exec_argv[0]);
		ms_vars->exit_value = 127;
		free_2d_arr((void***)&path_and_cmd);
		free(path);
		return (1);
	}
	return (0);
}

void	exec_cmd(t_ms_vars *ms_vars)
{	
	if (ms_vars->stdout_fd != STDOUT_FILENO)
		close(ms_vars->stdout_fd); //For the case of single execve cmd, close the saved stdout fd from earlier, refer to redirections.c lines 19-24
	if (ms_vars->stdin_fd != STDIN_FILENO)
		close(ms_vars->stdin_fd); //likewise for stdin
	/*
		Split into 2 cases.
		Case 1: cmd name contains a '/' character in any part of the string, this is an absolute or relative path, don't search PATH
		Case 2: otherwise, search PATH only. Do not try to access and execve the cmd by itself (e.g. access(minishell) followed by execve(minishell)) as this would succeed when it shouldn't. 
	*/
	if(ft_strchr(ms_vars->exec_argv[0], '/'))
	{
		if(execve(ms_vars->exec_argv[0], ms_vars->exec_argv, ms_vars->ep) == -1)
		{
			perror("execve unsuccessful");
			ms_vars->exit_value = 127;
		}
		return ;
	}
	else
		relative_path(ms_vars);	
}
