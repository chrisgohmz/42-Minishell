/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_str_arr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 21:56:49 by cgoh              #+#    #+#             */
/*   Updated: 2024/11/23 12:02:43 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	copy_old_to_new(char **restrict new_arr, char **restrict old_arr)
{
	size_t	i;

	i = 0;
	while (old_arr[i])
	{
		new_arr[i] = old_arr[i];
		i++;
	}
	free(old_arr);
}

char	**ft_realloc_str_arr(char **old_arr, size_t new_size)
{
	char	**new_arr;

	new_arr = ft_calloc(new_size, sizeof(char *));
	if (!new_arr)
		return (NULL);
	if (!old_arr)
		return (new_arr);
	copy_old_to_new(new_arr, old_arr);
	return (new_arr);
}
