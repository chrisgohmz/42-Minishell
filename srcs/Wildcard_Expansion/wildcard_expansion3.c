/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 20:00:51 by cgoh              #+#    #+#             */
/*   Updated: 2025/01/05 23:20:34 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_expansions_count(size_t *expansions_count, char ***expansions,
	t_wc_expand_vars *wc_e_vars)
{
	if (!*expansions_count)
	{
		*expansions[*expansions_count] = ft_strdup(wc_e_vars->pattern);
		if (!*expansions[(*expansions_count)++])
			return (free_2d_arr((void ***)&expansions));
	}
	if (*expansions_count > 1)
		*expansions = mergesort_expansions(*expansions, *expansions_count);
}
