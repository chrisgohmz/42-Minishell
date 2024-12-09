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

void	exec_cmd(t_ms_vars *ms_vars)
{
	char bin[] = "/usr/bin/";
	char *path;
	int len;

	len = ft_strlen(bin) + ft_strlen(ms_vars->exec_argv[0]);
	path = malloc(sizeof(char) * (len + 1));
	if (!path)
		return ;
	ft_strlcpy(path, bin, ft_strlen(bin) + 1);
	ft_strlcat(path, ms_vars->exec_argv[0], len + 1);
	if (ms_vars->stdout_fd != STDOUT_FILENO)
		close(ms_vars->stdout_fd); //For the case of single execve cmd, close the saved stdout fd from earlier, refer to redirections.c lines 19-24
	if (ms_vars->stdin_fd != STDIN_FILENO)
		close(ms_vars->stdin_fd); //likewise for stdin
	if(execve(path, ms_vars->exec_argv, ms_vars->ep) == -1)
	{
		perror("execve unsuccessful");
		ms_vars->exit_value = 127;
		free(path);
		return ;
	}
}
