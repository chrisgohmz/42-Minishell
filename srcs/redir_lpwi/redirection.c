/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:03:30 by lpwi              #+#    #+#             */
/*   Updated: 2024/11/19 19:39:16 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include "../../includes/minishell.h"
/** redirection - overwrite **/
/* > - standard output
   < - standard input */

/*
I have transferred redir_single_right to redirections.c and edited it for integration.
Do the same with single_left and double_right.
*/
int	redir_single_left(char *file_name)
{
	int	fd1;
	char	*line;

	fd1 = open(file_name, O_RDONLY);
	if (fd1 == -1)
		return (-1);
	while ((line = get_next_line(fd1)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd1);
	return 1;
}

int	redir_double_right(char *file_name, char **content)
{
	int	fd1;

	fd1 = open(file_name, O_WRONLY | O_CREAT | O_APPEND);
	if (fd1 == -1)
		return (-1);
	dup2(fd1, 1);
	int	i;

	i = 0;
	while(content[i])
	{
		printf("%s\n", content[i]);
		i++;
	}
	close(fd1);
	return 1;
}

int	arr_size(char **arr)
{
	int	i;

	i = 0;
	while(arr[i])
		i++;
	return (i);
}

void	heredoc_quoted(char **content)
{
	int	i;
	int	delim_index;

	i = 0;
	delim_index = arr_size(content) - 1;
	while(i < delim_index)
	{
		printf("%s\n", content[i]);
		i++;
	}
}
/* $(COMMAND) - if not found, display error that command not found, $VARIABLE - if not found, skip*/
/* loop through content and split again by white spaces then add to a new array of contents with newline*/
/* loop through new contents -  if $ spotted with (), run cmd exe. else if $ only, find the env and displayit. else just print. */

void	copy_arr(char **dest, char **src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(dest[i])
		i++;
	while(src[j])
	{
		dest[i] = ft_strdup(src[j]);
		i++;
		j++;
	}
	dest[i] = ft_strdup("\n");
}

void	heredoc_unquoted(char **content)
{
	int	i;
	int	j;
	int	k;
	int	delim_index;
	char	**new;
	char	**old;
	int	arr_size;
	char	*env_to_find;

	i = 0;
	new = NULL;
	delim_index = arr_size(content) - 1;
	while(i < delim_index)
	{
		old = ft_split(content[i]);
		new = ft_realloc_str_arr(old, arr_size(old) + arr_size(new) + 1);
		copy_arr(new, old);
		i++;
	}
	i = 0;
	while(new[i])
	{
		if (new[i][0] == '$' && new[i][1] == '(')
		{
			if(new[i][ft_strlen(new[i]) - 1] == ')')
				//run command if found else print error
			else
				printf("unexpected EOF while looking for matching `)'");
		}
		else if (new[i][0] == '$')
		{
			j = 1;
			k = 0;
			//while isalnum, store var and check if exists then display env
			while(ft_isalum(new[i][j]))
			{
				env_to_find[k] = new[i][j];
				j++;
				k++;
			}
			if(__environ(var_index(env_to_find)) != -1)
				printf("%s\n", __environ(var_index(env_to_find)));
			//then print all other remaining characters
			while(new[i][j])
				printf("%c", new[i][j]);
		}
		else
			printf("%s\n", content[i]);
		i++;
	}

}

int main(void)
{

	char **array = malloc(sizeof(char *) * 2 + 1);
	array[0] = strdup("hi");
	array[1] = strdup("world");
	printf("array[0] is %s\n", array[0]);
	printf("array[1] is %s\n", array[1]);

	int result = redir_double_right("test.txt", array);


	// int result = redir_single_left("file.txt");
	if (result == -1)
		printf("no read permission\n");
	return 1;
}
/** redirection - append **/
/* >> - standard output: append the output to the file
   << - heredoc: take a delimiter to mark the end of the document. the delimiter must be a single word that does not contain spaces or tabs. */
