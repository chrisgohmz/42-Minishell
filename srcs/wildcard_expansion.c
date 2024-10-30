/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:16:34 by cgoh              #+#    #+#             */
/*   Updated: 2024/10/30 21:55:02 by cgoh             ###   ########.fr       */
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
	char			*temp;
	char			*strs_to_join[2];
	int				i;
	int				j;
	int				save_j;

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
		if (entry->d_name[0] == '.')
		{
			entry = readdir(dirptr);
			continue;
		}
		i = 0;
		j = 0;
		save_j = -1;
		while (entry->d_name[i] || pattern[j])
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
				if (!check_wildcard_match(entry->d_name, pattern[j], &i))
					break;
				else
					save_j = j;
			}
			else if (entry->d_name[i] && save_j > 0)
			{
				j = save_j;
				if (!check_wildcard_match(entry->d_name, pattern[j], &i))
					break;
			}
			else
				break;
		}
		if (!entry->d_name[i] && !pattern[j])
		{
			strs_to_join[0] = expanded_str;
			strs_to_join[1] = entry->d_name;
			temp = ft_multi_strjoin(2, strs_to_join, " ");
			if (!temp)
				return (free(expanded_str), free(pattern), closedir(dirptr), NULL);
			free(expanded_str);
			expanded_str = temp;
		}
		errno = 0;
		entry = readdir(dirptr);
	}
	closedir(dirptr);
	if (errno)
	{
		perror("readdir");
		return (free(pattern), free(expanded_str), NULL);
	}
	if (!expanded_str[0])
		return (free(expanded_str), pattern);
	return (free(pattern), expanded_str);
}

char	*perform_wildcard_expansions(char *str)
{
	char	*expanded_str;
	char	**split_arr;
	int		i;

	split_arr = ft_multi_split(str, " \t");
	if (!split_arr)
		return (free(str), NULL);
	i = 0;
	while (split_arr[i])
	{
		if (ft_strchr(split_arr[i], '*'))
		{
			split_arr[i] = expand_wildcard(split_arr[i]);
			if (!split_arr[i])
				return (free_2d_malloc_array(&split_arr), free(str), NULL);
		}
		i++;
	}
	expanded_str = ft_multi_strjoin(i, split_arr, " ");
	free_2d_malloc_array(&split_arr);
	return (free(str), expanded_str);
}
