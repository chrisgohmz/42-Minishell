/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:57:59 by cgoh              #+#    #+#             */
/*   Updated: 2024/10/28 20:46:53 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static size_t	ft_strlcat_transform_metachar(char *dest, const char *src, size_t size, char dollar_char)
{
	size_t	src_n;
	size_t	dest_len;

	src_n = 0;
	dest_len = ft_strlen(dest);
	if (size <= dest_len)
		return (size + ft_strlen(src));
	while (src_n < size - 1 - dest_len && src[src_n])
	{
		if (src[src_n] == ' ' && dollar_char == DQUOTE_DOLLAR)
			dest[dest_len + src_n] = ESC_SPACE;
		else if (src[src_n] == '\t' && dollar_char == DQUOTE_DOLLAR)
			dest[dest_len + src_n] = ESC_TAB;
		else if (src[src_n] == '>')
			dest[dest_len + src_n] = ESC_RIGHT;
		else if (src[src_n] == '<')
			dest[dest_len + src_n] = ESC_LEFT;
		else
			dest[dest_len + src_n] = src[src_n];
		src_n++;
	}
	dest[dest_len + src_n] = '\0';
	return (ft_strlen(dest) + ft_strlen(&src[src_n]));
}

static void	fill_expanded_str(char *old_str, char *new_str, char **new_envp, size_t expanded_size)
{
	int	i;
	int	j;
	int	is_heredoc_delim;
	int	not_expanding;

	i = 0;
	j = 0;
	is_heredoc_delim = 0;
	not_expanding = 0;
	while (old_str[i])
	{
		if (old_str[i] == '<' && old_str[i + 1] == '<')
		{
			is_heredoc_delim = 1;
			not_expanding = 0;
			new_str[j++] = old_str[i++];
			new_str[j++] = old_str[i++];
		}
		if (!is_heredoc_delim && (old_str[i] == '$' || old_str[i] == DQUOTE_DOLLAR) && (ft_isalnum(old_str[i + 1]) || old_str[i + 1] == '_'))
		{
			if (old_str[i] == '$' || old_str[i] == DQUOTE_DOLLAR)
				j = ft_strlcat_transform_metachar(new_str, find_env_value(new_envp, old_str + i), expanded_size + 1, old_str[i]);
			i++;
			while (ft_isalnum(old_str[i]) || old_str[i] == '_')
				i++;
		}
		else if (old_str[i] != '"' && old_str[i] != '\'')
		{
			if (is_heredoc_delim && !ft_strchr(" \t><", old_str[i]))
				not_expanding = 1;
			else if (not_expanding && ft_strchr(" \t><", old_str[i]))
			{
				is_heredoc_delim = 0;
				not_expanding = 0;
			}
			new_str[j++] = old_str[i++];
		}
		else if ((old_str[i] == '"' || old_str[i] == '\'') && is_heredoc_delim)
			new_str[j++] = old_str[i++];
		else
			i++;
	}
}

static char	*allocate_expanded_str(char *str, char **new_envp, size_t *expanded_size)
{
	int		i;
	char	*expanded_str;
	int		is_heredoc_delim;
	int		not_expanding;

	*expanded_size = 0;
	i = 0;
	is_heredoc_delim = 0;
	not_expanding = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<')
		{
			is_heredoc_delim = 1;
			not_expanding = 0;
			i += 2;
			(*expanded_size) += 2;
		}
		if (!is_heredoc_delim && (str[i] == '$' || str[i] == DQUOTE_DOLLAR) && (ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
		{
			*expanded_size += ft_strlen(find_env_value(new_envp, str + i));
			i++;
			while (ft_isalnum(str[i	]) || str[i] == '_')
				i++;
		}
		else if (str[i] != '"' && str[i] != '\'')
		{
			if (is_heredoc_delim && !ft_strchr(" \t><", str[i]))
				not_expanding = 1;
			else if (not_expanding && ft_strchr(" \t><", str[i]))
			{
				is_heredoc_delim = 0;
				not_expanding = 0;
			}
			(*expanded_size)++;
			i++;
		}
		else if ((str[i] == '"' || str[i] == '\'') && is_heredoc_delim)
		{
			(*expanded_size)++;
			i++;
		}
		else
			i++;
	}
	expanded_str = ft_calloc(*expanded_size + 1, sizeof(char));
	return (expanded_str);
}

char	*perform_parameter_expansions(char *str, char **new_envp)
{
	char	*expanded_str;
	size_t	expanded_size;

	expanded_str = allocate_expanded_str(str, new_envp, &expanded_size);
	if (!expanded_str)
	{
		printf("Malloc failed for expanded_str\n");
		return (NULL);
	}
	fill_expanded_str(str, expanded_str, new_envp, expanded_size);
	return (expanded_str);
}
