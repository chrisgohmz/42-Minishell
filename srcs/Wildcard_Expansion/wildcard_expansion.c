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

#include "../../includes/minishell.h"

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
	size_t			arr_size;
	int				include_dot;
	int				i;
	int				j;
	int				save_j;

	arr_size = 1000;
	expansions = ft_calloc(arr_size, sizeof(char *));
	if (!expansions)
		return (perror("malloc"), NULL);
	dirptr = opendir(".");
	errno = 0;
	if (dirptr)
		entry = readdir(dirptr);
	include_dot = (pattern[0] == '.');
	while (dirptr && entry)
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
			(*expansions_count)++;
			if (*expansions_count + 1 > arr_size)
			{
				arr_size *= 2;
				expansions = ft_realloc_str_arr(expansions, arr_size);
				if (!expansions)
					return (perror("malloc"), closedir(dirptr), NULL);
			}
			expansions[*expansions_count - 1] = ft_strdup(entry->d_name);
			if (!expansions[*expansions_count - 1])
				return (closedir(dirptr), free_2d_arr((void ***)&expansions), NULL);
		}
		errno = 0;
		entry = readdir(dirptr);
	}
	if (errno)
		return (perror("readdir"), free_2d_arr((void ***)&expansions), closedir(dirptr), NULL);
	closedir(dirptr);
	if (!*expansions_count)
	{
		expansions[*expansions_count] = ft_strdup(pattern);
		if (!expansions[(*expansions_count)++])
			return (free_2d_arr((void ***)&expansions), NULL);
	}
	if (*expansions_count > 1)
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
	size_t	blocks_filled;
	int		i;

	split_arr = ft_multi_split(str, " \t");
	if (!split_arr)
		return (free(str), NULL);
	new_size = 1000;
	new_split_arr = ft_calloc(new_size, sizeof(char *));
	if (!new_split_arr)
		return (perror("malloc"), free(str), free_2d_arr((void ***)&split_arr), NULL);
	i = 0;
	blocks_filled = 1;
	while (split_arr[i])
	{
		expansions_count = 0;
		if (ft_strchr(split_arr[i], '*'))
		{
			expansions = expand_wildcard(split_arr[i], &expansions_count);
			if (!expansions)
				return (free_2d_arr((void ***)&split_arr), free_2d_arr((void ***)&new_split_arr), free(str), NULL);
			if (blocks_filled + expansions_count > new_size)
			{
				while (blocks_filled + expansions_count > new_size)
					new_size *= 2;
				new_split_arr = ft_realloc_str_arr(new_split_arr, new_size);
				if (!new_split_arr)
					return (free_2d_arr((void ***)&split_arr), free_2d_arr((void ***)&expansions), free(str), NULL);
			}
			ft_memcpy(new_split_arr + blocks_filled - 1, expansions, expansions_count * sizeof(char *));
			blocks_filled += expansions_count;
			free(expansions);
		}
		else
		{
			if (blocks_filled + 1 > new_size)
			{
				new_size *= 2;
				new_split_arr = ft_realloc_str_arr(new_split_arr, new_size);
				if (!new_split_arr)
					return (free_2d_arr((void ***)&split_arr), free_2d_arr((void ***)&expansions), free(str), NULL);
			}
			new_split_arr[blocks_filled - 1] = ft_strdup(split_arr[i]);
			if (!new_split_arr[blocks_filled++ - 1])
				return (free_2d_arr((void ***)&split_arr), free_2d_arr((void ***)&new_split_arr), free(str), NULL);
		}
		i++;
	}
	return (free(str), free_2d_arr((void ***)&split_arr), new_split_arr);
}
