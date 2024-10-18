/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:46:46 by cgoh              #+#    #+#             */
/*   Updated: 2024/05/22 19:43:12 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	fill_str(char *str, unsigned int n, int len)
{
	int		i;

	str[len] = '\0';
	i = len - 1;
	while (i >= 0)
	{
		str[i] = '0' + n % 10;
		n /= 10;
		i--;
	}
}

static int	count_length(unsigned int n)
{
	int		len;

	if (n == 0)
		return (1);
	len = 0;
	while (n > 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_utoa(unsigned int n)
{
	int				len;
	char			*str;

	len = count_length(n);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	fill_str(str, n, len);
	return (str);
}
