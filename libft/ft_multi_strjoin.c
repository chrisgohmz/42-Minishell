/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_strjoin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 21:30:05 by cgoh              #+#    #+#             */
/*   Updated: 2024/10/30 18:42:07 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	calc_total_len(int size, char **strs, char *sep)
{
	size_t	total_len;
	int		i;

	total_len = 0;
	i = 0;
	while (i < size)
	{
		total_len += ft_strlen(strs[i]);
		i++;
	}
	total_len += (size - 1) * ft_strlen(sep);
	return (total_len);
}

static int	append_str_sep(char *from_str, char *to_str, int k)
{
	size_t	j;

	j = 0;
	while (j < ft_strlen(from_str))
	{
		to_str[k] = from_str[j];
		j++;
		k++;
	}
	return (k);
}

static char	*join_strs(int size, char **strs, char *str, char *sep)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (i < size)
	{
		k = append_str_sep(strs[i], str, k);
		if (i < size - 1)
			k = append_str_sep(sep, str, k);
		i++;
	}
	str[k] = '\0';
	return (str);
}

char	*ft_multi_strjoin(int size, char **strs, char *sep)
{
	char	*str;
	int		total_len;

	if (size == 0)
	{
		str = malloc(1 * sizeof(char));
		if (!str)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	total_len = calc_total_len(size, strs, sep);
	str = malloc(total_len + 1);
	if (!str)
		return (NULL);
	join_strs(size, strs, str, sep);
	return (str);
}
