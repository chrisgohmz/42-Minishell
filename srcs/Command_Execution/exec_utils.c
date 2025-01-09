#include "../../includes/minishell.h"

int	abs_check_access(t_ms_vars *ms_vars, struct stat *statbuf)
{
	if (access(ms_vars->exec_argv[0], F_OK) != -1)
	{
		if (stat(ms_vars->exec_argv[0], statbuf) < 0)
			perror("stat");
		if (S_ISDIR(statbuf->st_mode))
		{
			ft_dprintf(STDERR_FILENO, "%s: Is a directory\n",
				ms_vars->exec_argv[0]);
			ms_vars->exit_value = 126;
			return (-1);
		}
	}
	return (0);
}

int	rel_check_access(t_ms_vars *ms_vars, struct stat *statbuf,
		char *path, char **bin)
{
	if (access(path, F_OK) != -1)
	{
		if (stat(path, statbuf) < 0)
			perror("stat");
		if (S_ISDIR(statbuf->st_mode))
		{
			ft_dprintf(STDERR_FILENO, "%s: Is a directory\n",
				ms_vars->exec_argv[0]);
			ms_vars->exit_value = 126;
			free_all(bin, path);
			return (-1);
		}
		if (access(path, X_OK) == -1)
		{
			perror(ms_vars->exec_argv[0]);
			ms_vars->exit_value = 126;
			free_all(bin, path);
			return (-1);
		}
		else
			return (0);
	}
	return (2);
}

void	free_all(char **bin, char *path)
{
	free_2d_arr((void ***)&bin);
	free(path);
}

void	exec_cmd_not_found_handler(t_ms_vars *ms_vars)
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
