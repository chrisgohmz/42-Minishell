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

static char	**expand_wildcard(char *pattern, size_t *expansions_count)
{
	DIR				*dirptr;
	struct dirent	*entry;
	char			**expansions;
	int				include_dot;
	int				i;
	int				j;
	int				save_j;

	dirptr = opendir(".");
	if (!dirptr)
	{
		perror("opendir");
		return (NULL);
	}
	errno = 0;
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
				if (!pattern[j])
					break;
				else if (!check_wildcard_match(entry->d_name, pattern[j], &i))
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
		if (!pattern[j])
		{
			expansions = ft_realloc_str_arr(expansions, *expansions_count + 2);
			if (!expansions)
				return (closedir(dirptr), NULL);
			expansions[(*expansions_count)++] = ft_strdup(entry->d_name);
			if (!expansions[*expansions_count - 1])
				return (closedir(dirptr), free_2d_malloc_array(&expansions), NULL);
		}
		errno = 0;
		entry = readdir(dirptr);
	}
	closedir(dirptr);
	if (errno)
		return (perror("readdir"), free_2d_malloc_array(&expansions), NULL);
	if (!*expansions_count)
	{
		expansions = ft_realloc_str_arr(expansions, *expansions_count + 2);
		if (!expansions)
			return (NULL);
		expansions[(*expansions_count)++] = ft_strdup(pattern);
		if (!expansions[*expansions_count - 1])
			return (free_2d_malloc_array(&expansions), NULL);
	}
	expansions = mergesort_expansions(expansions, *expansions_count);
	return (expansions);
}

char	**perform_wildcard_expansions(char *str)
{
	char	**split_arr;
	char	**new_split_arr;
	char	**expansions;
	size_t	expansions_count;
	size_t	new_size;
	int		i;
	int		j;

	split_arr = ft_multi_split(str, " \t");
	if (!split_arr)
		return (free(str), NULL);
	new_split_arr = NULL;
	i = 0;
	new_size = 0;
	while (split_arr[i])
	{
		expansions_count = 0;
		if (ft_strchr(split_arr[i], '*'))
		{
			expansions = expand_wildcard(split_arr[i], &expansions_count);
			if (!expansions)
				return (free_2d_malloc_array(&split_arr), free(str), NULL);
			new_split_arr = ft_realloc_str_arr(new_split_arr, new_size + expansions_count + 1);
			if (!new_split_arr)
				return (free_2d_malloc_array(&split_arr), free_2d_malloc_array(&expansions), free(str), NULL);
			j = 0;
			while (expansions[j])
				new_split_arr[new_size++] = expansions[j++];
			free(expansions);
		}
		else
		{
			new_split_arr = ft_realloc_str_arr(new_split_arr, ++new_size + 1);
			new_split_arr[new_size - 1] = ft_strdup(split_arr[i]);
		}
		i++;
	}
	return (free(str), free_2d_malloc_array(&split_arr), new_split_arr);
}
