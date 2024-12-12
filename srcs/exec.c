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

extern int errno; //no need to include this, nor are we allowed to since it's a global var, it's alrdy defined in <errno.h>

/*
cgoh: Good start! Now I need u to modify it such that it searches $PATH, not just /usr/bin/.
Handle command when given absolute/relative path (e.g. /usr/bin/cat, ./minishell).
exit status may also not be 127 on failure, see https://www.gnu.org/software/bash/manual/bash.html#Exit-Status.
may want to look into access() function.
*/

static char **store_path(t_ms_vars *ms_vars)
{
	char *path;
	char **bin;
	int path_len;
	int index;
	int i;
	int j;

	index = find_unset_pos(ms_vars, "PATH");
	i = 5;
	j = 0;
	path_len = ft_strlen(ms_vars->ep[index]) - i;
	path = malloc(sizeof(char) * (path_len + 1));
	if (!path)
	{
		perror("malloc failure\n");
		return (NULL);
	}
	while (ms_vars->ep[index][i])
	{
		path[j] = ms_vars->ep[index][i];
		j++;
		i++;
	}
	path[j] = '\0';
	//cgoh: I think getenv() does the job for lines 33-49
	bin  = ft_split(path, ':');
	if (!bin)
	{
		perror("split failure\n");
		return (NULL);
	}
	free(path);
	return (bin);
}

static int relative_path(t_ms_vars *ms_vars)
{
	int i;
	char **bin;
	int len;
	char *path;

	i = 0;
	bin = store_path(ms_vars);
	if (!bin)
	{
		perror("store path failure\n");
		return ;
	}
	while (bin[i])
	{
		len = ft_strlen(bin[i]) + ft_strlen(ms_vars->exec_argv[0]) + 1;
		path = malloc(sizeof(char) * (len + 1));
		if (!path)
			return (1);
		ft_strlcpy(path, bin[i], ft_strlen(bin[i]) + 1);
		ft_strlcat(path, "/", len + 1);
		ft_strlcat(path, ms_vars->exec_argv[0], len + 1);
		//cgoh: ft_multi_strjoin is probably easier
		if(access(path, F_OK &/*should be bitwise OR not bitwise AND*/ X_OK) != -1)
			break ;
		i++;
	}
	if(execve(path, ms_vars->exec_argv, ms_vars->ep) == -1)
	{
		perror("execve unsuccessful");
		ms_vars->exit_value = 127;
		free(path);
		return (1);
	}
	return (0);
}

void	exec_cmd(t_ms_vars *ms_vars)
{
	char **bin;
	char *path;
	int len;
	int i;
	char	cwd[PATH_MAX];
	
	if (ms_vars->stdout_fd != STDOUT_FILENO)
		close(ms_vars->stdout_fd); //For the case of single execve cmd, close the saved stdout fd from earlier, refer to redirections.c lines 19-24
	if (ms_vars->stdin_fd != STDIN_FILENO)
		close(ms_vars->stdin_fd); //likewise for stdin
	/*
		Split into 2 cases.
		Case 1: cmd name contains a '/' character in any part of the string, this is an absolute or relative path, don't search PATH
		Case 2: otherwise, search PATH only. Do not try to access and execve the cmd by itself (e.g. access(minishell) followed by execve(minishell)) as this would succeed when it shouldn't. 
	*/
	if(ms_vars->exec_argv[0][0] == '/')
	{
		if(execve(ms_vars->exec_argv[0], ms_vars->exec_argv, ms_vars->ep) == -1)
		{
			perror("execve unsuccessful");
			ms_vars->exit_value = 127;
		}
		return ;
	}
	else if(ms_vars->exec_argv[0][0] == '.' && ms_vars->exec_argv[0][1] == '/')//need tosplit the directory?? cgoh: don't need
	{
		if(getcwd(cwd, sizeof(cwd)))
			path = ft_strdup(cwd);
		else
			return ;
		
	}
	else
		relative_path(ms_vars);	
}
