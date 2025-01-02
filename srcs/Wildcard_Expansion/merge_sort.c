/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 10:37:10 by cgoh              #+#    #+#             */
/*   Updated: 2025/01/02 20:43:45 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	merge(char **restrict arr2, char **restrict arr1, t_mergesort_vars ms_vars)
{
	int	i;
	int	j;
	int	k;

	i = ms_vars.start;
	j = ms_vars.middle;
	k = ms_vars.start;
	while (k < ms_vars.end)
	{
		if (i < ms_vars.middle && (j >= ms_vars.end || ft_strncmp(arr1[i], arr1[j], 256) <= 0))
			arr2[k] = arr1[i++];
		else
			arr2[k] = arr1[j++];
		k++;
	}
}

static void	split_merge(char **arr2, char **arr1, int start, int end)
{
	int					middle;
	t_mergesort_vars	ms_vars;

	if (end - start <= 1)
		return ;
	middle = (start + end) / 2;
	split_merge(arr1, arr2, start, middle);
	split_merge(arr1, arr2, middle, end);
	ms_vars.start = start;
	ms_vars.middle = middle;
	ms_vars.end = end;
	merge(arr2, arr1, ms_vars);
}

static char	**copy_expansions(char **expansions, int expansions_count)
{
	char	**expansions_copy;

	expansions_copy = malloc(expansions_count * sizeof(char *));
	if (!expansions_copy)
	{
		perror("malloc");
		free_2d_arr((void ***)&expansions);
		return (NULL);
	}
	ft_memcpy(expansions_copy, expansions, expansions_count * sizeof(char *));
	return (expansions_copy);
}

char	**mergesort_expansions(char **expansions, int expansions_count)
{
	char				**expansions_copy;

	expansions_copy = copy_expansions(expansions, expansions_count);
	if (!expansions_copy)
		return (NULL);
	split_merge(expansions, expansions_copy, 0, expansions_count);
	free(expansions_copy);
	return (expansions);
}
