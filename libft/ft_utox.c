/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:28:18 by cgoh              #+#    #+#             */
/*   Updated: 2024/05/22 18:15:53 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	fill_x(char *x, unsigned int n, int index, char *hex)
{
	if (n == 0)
		return ;
	fill_x(x, n / 16, index - 1, hex);
	x[index] = hex[n % 16];
}

static int	get_len(unsigned int n)
{
	int		i;

	i = 1;
	n /= 16;
	while (n)
	{
		n /= 16;
		i++;
	}
	return (i);
}

char	*ft_utox(unsigned int n, char format)
{
	char	*x;
	char	hex[17];
	int		len;

	if (format == 'x')
		ft_strlcpy(hex, "0123456789abcdef", sizeof(hex));
	else if (format == 'X')
		ft_strlcpy(hex, "0123456789ABCDEF", sizeof(hex));
	else
		return (NULL);
	len = get_len(n);
	x = malloc((len + 1) * sizeof(char));
	if (!x)
		return (NULL);
	if (n == 0)
		x[0] = '0';
	else
		fill_x(x, n, len - 1, hex);
	x[len] = '\0';
	return (x);
}
