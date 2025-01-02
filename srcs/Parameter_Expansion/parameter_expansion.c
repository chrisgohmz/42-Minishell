/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:57:59 by cgoh              #+#    #+#             */
/*   Updated: 2024/11/17 17:47:15 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	ft_strlcat_transform_metachar(char *dest, const char *src,
	size_t size, char dollar_char)
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

static int	append_expansion(char *old_str, char *new_str, int *i,
	size_t expanded_size)
{
	int	j;

	j = ft_strlcat_transform_metachar(new_str,
			ft_getenv(old_str + *i + 1), expanded_size + 1,
			old_str[*i]);
	(*i)++;
	while (ft_isalnum(old_str[*i]) || old_str[*i] == '_')
		(*i)++;
	return (j);
}

static void	fill_expanded_str(char *old_str, char *new_str,
	t_ms_vars *ms_vars, size_t expanded_size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (old_str[i])
	{
		if ((old_str[i] == '$' || old_str[i] == DQUOTE_DOLLAR)
			&& (ft_isalnum(old_str[i + 1]) || old_str[i + 1] == '_'))
			j = append_expansion(old_str, new_str, &i, expanded_size);
		else if ((old_str[i] == '$' || old_str[i] == DQUOTE_DOLLAR)
			&& old_str[i + 1] == '?')
		{
			if (ms_vars->exit_value == 0)
				new_str[j++] = '0';
			else
				insert_exit_value(ms_vars->exit_value, new_str, &j);
			i += 2;
		}
		else
			new_str[j++] = old_str[i++];
	}
}

static void	allocate_expanded_str(char *str, t_ms_vars *ms_vars,
	size_t *expanded_size)
{
	int		i;

	*expanded_size = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i] == '$' || str[i] == DQUOTE_DOLLAR)
			&& (ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
		{
			*expanded_size += ft_strlen(ft_getenv(str + i++ + 1));
			while (ft_isalnum(str[i]) || str[i] == '_')
				i++;
		}
		else if ((str[i] == '$' || str[i] == DQUOTE_DOLLAR)
			&& str[i + 1] == '?')
		{
			*expanded_size += get_exit_value_len(ms_vars->exit_value);
			i += 2;
		}
		else
		{
			(*expanded_size)++;
			i++;
		}
	}
}

char	*perform_parameter_expansions(char *str, t_ms_vars *ms_vars)
{
	char	*expanded_str;
	size_t	expanded_size;

	allocate_expanded_str(str, ms_vars, &expanded_size);
	expanded_str = ft_calloc(expanded_size + 1, sizeof(char));
	if (!expanded_str)
	{
		perror("malloc");
		return (NULL);
	}
	fill_expanded_str(str, expanded_str, ms_vars, expanded_size);
	return (expanded_str);
}
