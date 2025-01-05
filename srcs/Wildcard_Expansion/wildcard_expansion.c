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

static void	add_pattern(char ***new_split_arr, t_wildcard_vars *wc_vars)
{
	if (wc_vars->blocks_filled + 1 > wc_vars->new_size)
	{
		wc_vars->new_size *= 2;
		*new_split_arr = ft_realloc_str_arr(*new_split_arr, wc_vars->new_size);
		if (!*new_split_arr)
			return ;
	}
	(*new_split_arr)[wc_vars->blocks_filled - 1] = ft_strdup(wc_vars->\
		split_arr[wc_vars->i]);
	if (!new_split_arr[wc_vars->blocks_filled++ - 1])
		return (free_2d_arr((void ***)&new_split_arr));
}

static void	add_expansions(char ***new_split_arr, t_wildcard_vars *wc_vars)
{
	char	**expansions;
	size_t	expansions_count;

	expansions_count = 0;
	expansions = expand_wildcard(wc_vars->split_arr[wc_vars->i],
			&expansions_count);
	if (!expansions)
		return (free_2d_arr((void ***)new_split_arr));
	if (wc_vars->blocks_filled + expansions_count > wc_vars->new_size)
	{
		while (wc_vars->blocks_filled + expansions_count > wc_vars->new_size)
			wc_vars->new_size *= 2;
		*new_split_arr = ft_realloc_str_arr(*new_split_arr, wc_vars->new_size);
		if (!*new_split_arr)
			return (free_2d_arr((void ***)&expansions));
	}
	ft_memcpy(new_split_arr + wc_vars->blocks_filled - 1, expansions,
		expansions_count * sizeof(char *));
	wc_vars->blocks_filled += expansions_count;
	free(expansions);
}

static void	fill_new_split_arr(char ***new_split_arr, t_wildcard_vars *wc_vars)
{
	wc_vars->blocks_filled = 1;
	wc_vars->i = 0;
	while (wc_vars->split_arr[wc_vars->i])
	{
		if (ft_strchr(wc_vars->split_arr[wc_vars->i], '*'))
			add_expansions(new_split_arr, wc_vars);
		else
			add_pattern(new_split_arr, wc_vars);
		wc_vars->i++;
	}
}

char	**perform_wildcard_expansions(char *str)
{
	char			**new_split_arr;
	t_wildcard_vars	wc_vars;

	wc_vars.split_arr = ft_multi_split(str, " \t");
	if (!wc_vars.split_arr)
		return (free(str), NULL);
	wc_vars.new_size = 1000;
	new_split_arr = ft_calloc(wc_vars.new_size, sizeof(char *));
	if (!new_split_arr)
		return (perror("malloc"), free(str),
			free_2d_arr((void ***)&wc_vars.split_arr), NULL);
	fill_new_split_arr(&new_split_arr, &wc_vars);
	return (free(str), free_2d_arr((void ***)&wc_vars.split_arr),
		new_split_arr);
}
