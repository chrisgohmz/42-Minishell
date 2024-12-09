/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 01:59:25 by cgoh              #+#    #+#             */
/*   Updated: 2024/12/08 22:39:42 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	disable_value_word_splitting(char *str)
{
	int		i;
	bool	disable;
	
	i = 0;
	disable = false;
	while (str[i])
	{
		if (str[i] == '=')
			disable = true;
		else if (disable && str[i] == '$')
			str[i] = DQUOTE_DOLLAR;
		else if (disable && str[i] == '*')
			str[i] = ESC_WILDCARD;
		i++;
	}
}

static char	*remove_quoted_null_args(char *str)
{
	char	*new_str;
	char	**split_arr;
	int		i;
	int		j;
	int		k;
	size_t	len;

	len = ft_strlen(str);
	new_str = ft_calloc(len + 1, sizeof(char));
	if (!new_str)
		return (free(str), NULL);
	split_arr = ft_multi_split(str, " \t");
	if (!split_arr)
		return (free(str), free(new_str), NULL);
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
			continue;
		}
		k = -1;
		while (split_arr[i][++k])
			if (!(split_arr[i][k] == DQUOTE && split_arr[i][k + 1] == DQUOTE)
			&& !(split_arr[i][k] == SQUOTE && split_arr[i][k + 1] == SQUOTE))
				new_str[j++] = split_arr[i][k];
			else
				k++;
		if (split_arr[i + 1])
			new_str[j++] = ' ';
	}
	free(str);
	free_2d_arr((void ***)&split_arr);
	return (new_str);
}

char	**do_expansions(char *str, t_ms_vars *ms_vars)
{
	char	*expanded_str;
	char	**split_arr;
	
	expanded_str = perform_parameter_expansions(str, ms_vars);
	if (!expanded_str)
		return (NULL);
	expanded_str = remove_quoted_null_args(expanded_str);
	if (!expanded_str)
		return (NULL);
	split_arr = perform_wildcard_expansions(expanded_str);
	if (!split_arr)
		return (NULL);
	return (split_arr);
}
