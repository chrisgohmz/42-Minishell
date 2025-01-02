/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 19:48:32 by cgoh              #+#    #+#             */
/*   Updated: 2025/01/02 20:43:19 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	fill_new_str(char *old_str, char *new_str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (old_str[i])
	{
		if (old_str[i] != DQUOTE && old_str[i] != SQUOTE)
			new_str[j++] = old_str[i++];
		else
			i++;
	}
}

char	*remove_quotes(char *old_str)
{
	size_t	len;
	char	*new_str;

	len = ft_strlen(old_str);
	new_str = ft_calloc(len + 1, sizeof(char));
	if (!new_str)
		return (perror("malloc"), free(old_str), NULL);
	fill_new_str(old_str, new_str);
	free(old_str);
	return (new_str);
}
