/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 17:45:27 by cgoh              #+#    #+#             */
/*   Updated: 2025/01/05 20:17:17 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_wildcard_match(char *entry_name, char delimiter, int *i)
{
	while (entry_name[*i] && entry_name[*i] != delimiter)
		(*i)++;
	return (entry_name[*i] == delimiter);
}

static bool	check_save_point_match(t_wc_expand_vars *wc_e_vars, int *i,
	int *j, int save_j)
{
	if (wc_e_vars->entry->d_name[*i] && save_j > 0)
	{
		*j = save_j;
		if (!check_wildcard_match(wc_e_vars->entry->d_name,
				wc_e_vars->pattern[*j], i))
			return (false);
		else
			return (true);
	}
	else
		return (false);
}

static void	check_pattern_match(t_wc_expand_vars *wc_e_vars, int *j)
{
	int	i;
	int	save_j;

	i = 0;
	save_j = -1;
	while (wc_e_vars->entry->d_name[i] || wc_e_vars->pattern[*j])
	{
		if (wc_e_vars->pattern[*j] == '*')
			skip_multiple_wildcards_and_check_wildcard_match(&i,
				j, &save_j, wc_e_vars);
		else if (wc_e_vars->entry->d_name[i] != wc_e_vars->pattern[*j]
			&& !check_save_point_match(wc_e_vars, &i, j, save_j))
			break ;
		else
		{
			i++;
			(*j)++;
		}
	}
}

static void	add_matches(char ***expansions,
	size_t *expansions_count, t_wc_expand_vars *wc_e_vars)
{
	int	j;

	j = 0;
	if (wc_e_vars->entry->d_name[0] == '.' && wc_e_vars->pattern[0] != '.')
		return ;
	check_pattern_match(wc_e_vars, &j);
	if (!wc_e_vars->pattern[j])
	{
		(*expansions_count)++;
		if (*expansions_count + 1 > wc_e_vars->arr_size)
		{
			wc_e_vars->arr_size *= 2;
			*expansions = ft_realloc_str_arr(*expansions, wc_e_vars->arr_size);
			if (!expansions)
				return (perror("malloc"));
		}
		(*expansions)[*expansions_count - 1] = ft_strdup(wc_e_vars->\
		entry->d_name);
		if (!expansions[*expansions_count - 1])
			return (free_2d_arr((void ***)&expansions), perror("malloc"));
	}
}

char	**expand_wildcard(char *pattern, size_t *expansions_count)
{
	char				**expansions;
	t_wc_expand_vars	wc_e_vars;

	wc_e_vars.pattern = pattern;
	wc_e_vars.arr_size = 1000;
	expansions = ft_calloc(wc_e_vars.arr_size, sizeof(char *));
	if (!expansions)
		return (perror("malloc"), NULL);
	wc_e_vars.dirptr = opendir(".");
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
	return (expansions);
}
