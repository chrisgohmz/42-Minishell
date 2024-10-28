/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:16:34 by cgoh              #+#    #+#             */
/*   Updated: 2024/10/28 22:37:02 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_wildcard_match(char *entry_name, char delimiter, int *i)
{
	while (entry_name[*i] && entry_name[*i] != delimiter)
		(*i)++;
	return (entry_name[*i] == delimiter);
}

static char	*expand_wildcard(char *pattern)
{
	DIR				*dirptr;
	struct dirent	*entry;
	char			*expanded_str;
	int				i;
	int				j;

	dirptr = opendir(".");
	if (!dirptr)
	{
		perror("opendir");
		return (free(pattern), NULL);
	}
	expanded_str = ft_strdup("");
	if (!expanded_str)
		return (free(pattern), closedir(dirptr), NULL);
	errno = 0;
	entry = readdir(dirptr);
	while (entry)
	{
		i = 0;
		j = 0;
		while (entry->d_name[i] && pattern[j])
		{
			if (entry->d_name[i] == pattern[j])
			{
				i++;
				j++;
			}
			else if (pattern[j] == '*')
			{
				while (pattern[j] == '*')
					j++;
				if (!pattern[j])
					expanded_str = ft_strjoin(expanded_str, " ");
					if (!expanded_str)
						return (NULL);
					expanded_str = ft_strjoin(expanded_str, entry->d_name);
						return (NULL);
				if (!check_wildcard_match(entry->d_name, pattern[j], &i))
					break;
				else
					break;
			}
		}
		errno = 0;
		entry = readdir(dirptr);
	}
	closedir(dirptr);
	if (errno)
	{
		perror("readdir");
		return (NULL);
	}
	if (!expanded_str[0]);
		return (free(expanded_str), pattern);
	return (free(pattern), expanded_str);
}

static char	*allocate_expanded_str(char *str, size_t *expanded_size)
{
	char	*expanded_str;
	char	**split_arr;
	int		i;

	split_arr = ft_multi_split(str, " \t");
	if (!split_arr)
		return (NULL);
	i = 0;
	while (split_arr[i])
	{
		if (ft_strchr(split_arr[i], '*'))
		{
			split_arr[i] = expand_wildcard(split_arr[i]);
			if (!split_arr[i])
				return (NULL);
		}
		i++;
	}
	return (expanded_str);
}

char	*perform_wildcard_expansions(char *str)
{
	char	*expanded_str;
	size_t	expanded_size;

	expanded_str = allocate_expanded_str(str, &expanded_size);
	return (expanded_str);
}
