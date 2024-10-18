/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_tree3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:57:59 by cgoh              #+#    #+#             */
/*   Updated: 2024/10/18 18:37:21 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	ft_strlcat_transform_metachar(char *dest, const char *src, size_t size)
{
	size_t	src_n;
	size_t	dest_len;

	src_n = 0;
	dest_len = ft_strlen(dest);
	if (size <= dest_len)
		return (size + ft_strlen(src));
	while (src_n < size - 1 - dest_len && src[src_n])
	{
		if (src[src_n] == ' ')
			dest[dest_len + src_n] = ESC_SPACE;
		else if (src[src_n] == '\t')
			dest[dest_len + src_n] = ESC_TAB;
		else
			dest[dest_len + src_n] = src[src_n];
		src_n++;
	}
	dest[dest_len + src_n] = '\0';
	return (ft_strlen(dest) + ft_strlen(&src[src_n]));
}

void	fill_expanded_str(char *old_str, char *new_str, char **new_envp, size_t expanded_size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (old_str[i])
	{
		if ((old_str[i] == '$' || old_str[i] == DQUOTE_DOLLAR) && (ft_isalnum(old_str[i + 1]) || old_str[i + 1] == '_'))
		{
			if (old_str[i] == '$')
				j = ft_strlcat(new_str, find_env_value(new_envp, old_str + i), expanded_size + 1);
			else
				j = ft_strlcat_transform_metachar(new_str, find_env_value(new_envp, old_str + i), expanded_size + 1);
			i++;
			while (ft_isalnum(old_str[i]) || old_str[i] == '_')
				i++;
		}
		else if (old_str[i] != '"' && old_str[i] != '\'')
			new_str[j++] = old_str[i++];
		else
			i++;
	}
}
