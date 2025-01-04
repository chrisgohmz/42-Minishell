/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_null_arg_quote_removal.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 18:22:05 by cgoh              #+#    #+#             */
/*   Updated: 2025/01/04 18:44:02 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	fill_new_str(char *new_str, size_t len, char **split_arr)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	j = 0;
	while (split_arr[++i])
	{
		k = 0;
		while (split_arr[i][k] == SQUOTE || split_arr[i][k] == DQUOTE)
			k++;
		if (!split_arr[i][k])
		{
			j = ft_strlcat(new_str + j, split_arr[i], len + 1);
			continue ;
		}
		k = -1;
		while (split_arr[i][++k])
			if (split_arr[i][k] != DQUOTE && split_arr[i][k] != SQUOTE)
				new_str[j++] = split_arr[i][k];
		if (split_arr[i + 1])
			new_str[j++] = ' ';
	}
}

char	*remove_quotes_in_non_null_args(char *str)
{
	char	*new_str;
	char	**split_arr;
	size_t	len;

	len = ft_strlen(str);
	new_str = ft_calloc(len + 1, sizeof(char));
	if (!new_str)
		return (free(str), NULL);
	split_arr = ft_multi_split(str, " \t");
	if (!split_arr)
		return (free(str), free(new_str), NULL);
	fill_new_str(new_str, len, split_arr);
	free(str);
	free_2d_arr((void ***)&split_arr);
	return (new_str);
}
