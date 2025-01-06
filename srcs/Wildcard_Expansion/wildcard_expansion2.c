/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 17:45:27 by cgoh              #+#    #+#             */
/*   Updated: 2025/01/05 23:27:04 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	check_pattern_end_match(char *entry, char *substr,
	char *pattern)
{
	size_t	substr_len;

	while (*pattern)
		pattern++;
	if (*(pattern - 1) == WILDCARD)
		return (true);
	while (*entry)
		entry++;
	substr_len = ft_strlen(substr);
	entry -= substr_len;
	if (ft_strncmp(entry, substr, substr_len))
		return (false);
	return (true);
}

static bool	check_pattern_start_match(char *entry, char *substr, char *pattern)
{
	if (pattern[0] == WILDCARD)
		return (true);
	if (ft_strncmp(entry, substr, ft_strlen(substr)))
		return (false);
	return (true);
}

static bool	check_pattern_match(t_wc_expand_vars *wc_e_vars)
{
	char	**pattern_substr_arr;
	int		i;
	char	*substr_pos;

	pattern_substr_arr = ft_split(wc_e_vars->pattern, WILDCARD);
	if (!pattern_substr_arr)
		return (perror("malloc"), false);
	i = -1;
	substr_pos = wc_e_vars->entry->d_name;
	while (pattern_substr_arr[++i])
	{
		substr_pos = ft_strnstr(substr_pos, pattern_substr_arr[i],
				ft_strlen(wc_e_vars->entry->d_name));
		if (!substr_pos)
			return (free_2d_arr((void ***)&pattern_substr_arr), false);
		substr_pos += ft_strlen(pattern_substr_arr[i]);
	}
	if (!check_pattern_start_match(wc_e_vars->entry->d_name,
			pattern_substr_arr[0], wc_e_vars->pattern))
		return (free_2d_arr((void ***)&pattern_substr_arr), false);
	if (i > 0 && !check_pattern_end_match(wc_e_vars->entry->d_name,
			pattern_substr_arr[i - 1], wc_e_vars->pattern))
		return (free_2d_arr((void ***)&pattern_substr_arr), false);
	return (free_2d_arr((void ***)&pattern_substr_arr), true);
}

static void	add_matches(char ***expansions,
	size_t *expansions_count, t_wc_expand_vars *wc_e_vars)
{
	if (wc_e_vars->entry->d_name[0] == '.' && wc_e_vars->pattern[0] != '.')
		return ;
	if (check_pattern_match(wc_e_vars))
	{
		(*expansions_count)++;
		if (*expansions_count + 1 > wc_e_vars->arr_size)
		{
			wc_e_vars->arr_size *= 2;
			*expansions = ft_realloc_str_arr(*expansions, wc_e_vars->arr_size);
			if (!*expansions)
				return (perror("malloc"));
		}
		(*expansions)[*expansions_count - 1] = ft_strdup(wc_e_vars->\
		entry->d_name);
		if (!(*expansions)[*expansions_count - 1])
			return (free_2d_arr((void ***)expansions), perror("malloc"));
	}
}

char	**expand_wildcard(char *pattern, size_t *expansions_count)
{
	char				**expansions;
	t_wc_expand_vars	wc_e_vars;

	wc_e_vars.pattern = revert_transform(transform_wildcard(pattern));
	wc_e_vars.arr_size = 1000;
	expansions = ft_calloc(wc_e_vars.arr_size, sizeof(char *));
	if (!expansions)
		return (perror("malloc"), NULL);
	wc_e_vars.dirptr = opendir(".");
	errno = 0;
	if (wc_e_vars.dirptr)
		wc_e_vars.entry = readdir(wc_e_vars.dirptr);
	while (wc_e_vars.dirptr && wc_e_vars.entry)
	{
		add_matches(&expansions, expansions_count, &wc_e_vars);
		wc_e_vars.entry = readdir(wc_e_vars.dirptr);
	}
	if (errno)
		return (perror("readdir"), free_2d_arr((void ***)&expansions),
			closedir(wc_e_vars.dirptr), NULL);
	closedir(wc_e_vars.dirptr);
	revert_wildcard_transform(wc_e_vars.pattern);
	check_expansions_count(expansions_count, &expansions, &wc_e_vars);
	return (expansions);
}
