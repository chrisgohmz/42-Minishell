/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:16:34 by cgoh              #+#    #+#             */
/*   Updated: 2024/11/19 18:44:01 by cgoh             ###   ########.fr       */
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
	char			**expansions;
	int				expansions_count;
	int				include_dot;
	int				i;
	int				j;
	int				save_j;

	dirptr = opendir(".");
	if (!dirptr)
	{
		perror("opendir");
		return (free(pattern), NULL);
	}
	errno = 0;
	expansions_count = 0;
	expansions = NULL;
	entry = readdir(dirptr);
	include_dot = (pattern[0] == '.');
	while (entry)
	{
		if (entry->d_name[0] == '.' && !include_dot)
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
			expansions = ft_realloc_str_arr(expansions, expansions_count + 2);
			if (!expansions)
				return (closedir(dirptr), free(pattern), NULL);
			expansions[expansions_count++] = ft_strdup(entry->d_name);
			if (!expansions[expansions_count - 1])
				return (closedir(dirptr), free(pattern), free_2d_malloc_array(&expansions), NULL);
		}
		errno = 0;
		entry = readdir(dirptr);
	}
	if (errno)
		return (perror("readdir"), free(pattern), closedir(dirptr), free_2d_malloc_array(&expansions), NULL);
	if (!expansions_count)
		return (closedir(dirptr), free_2d_malloc_array(&expansions), pattern);
	expansions = mergesort_expansions(expansions, expansions_count);
	if (!expansions)
		return (closedir(dirptr), free(pattern), NULL);
	expanded_str = ft_multi_strjoin(expansions_count, expansions, " ");
	return (closedir(dirptr), free(pattern), free_2d_malloc_array(&expansions), expanded_str);
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
