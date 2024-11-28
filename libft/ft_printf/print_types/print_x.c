/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:39:08 by cgoh              #+#    #+#             */
/*   Updated: 2024/11/29 02:30:55 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static char	*malloc_str_x(unsigned int n, t_format *format_lst, char format)
{
	int		len;
	char	*x_str;
	char	*formatted_x;

	x_str = ft_utox(n, format);
	if (!x_str)
		return (NULL);
	len = ft_strlen(x_str) - (n == 0 && format_lst->precision == 0);
	if (format_lst->precision > len)
		len = format_lst->precision;
	free(x_str);
	if (ft_strchr(format_lst->flags, '#') && n != 0)
		len += 2;
	formatted_x = malloc((len + 1) * sizeof(char));
	if (!formatted_x)
		return (NULL);
	ft_memset(formatted_x, 1, len);
	formatted_x[len] = '\0';
	return (formatted_x);
}

static int	fill_formatted_x(char *formatted_x, unsigned int n
, char format, t_format *format_lst)
{
	char	*x_str;
	int		i;
	int		x_start;

	x_str = ft_utox(n, format);
	if (!x_str)
		return (0);
	i = 0;
	if (ft_strchr(format_lst->flags, '#') && n != 0)
	{
		formatted_x[i++] = '0';
		formatted_x[i++] = format;
	}
	x_start = ft_strlen(formatted_x) - ft_strlen(x_str);
	while (i < x_start)
		formatted_x[i++] = '0';
	formatted_x[i] = '\0';
	ft_strlcat(formatted_x, x_str, x_start + ft_strlen(x_str) + 1);
	free(x_str);
	return (1);
}

static void	print_formatted_x(char *formatted_x, t_format *format_lst)
{
	int		left;
	char	*flags;
	int		width;
	int		fill_zeroes;

	flags = format_lst->flags;
	width = format_lst->width;
	left = (ft_strchr(flags, '-') != NULL);
	fill_zeroes = (format_lst->precision < 0 && ft_strchr(flags, '0'));
	if (fill_zeroes && ft_strchr(flags, '#'))
		ft_putstr_fd("0x", format_lst->fd);
	while (!left && width-- > (int)ft_strlen(formatted_x))
	{
		if (fill_zeroes)
			ft_putchar_fd('0', format_lst->fd);
		else
			ft_putchar_fd(' ', format_lst->fd);
	}
	ft_putstr_fd(formatted_x + 2 * (fill_zeroes && ft_strchr(flags, '#')),
		format_lst->fd);
	while (width-- > (int)ft_strlen(formatted_x))
		ft_putchar_fd(' ', format_lst->fd);
}

int	print_x(t_format *format_lst, unsigned int n, char format)
{
	char	*formatted_x;
	int		len;

	formatted_x = malloc_str_x(n, format_lst, format);
	if (!formatted_x)
		return (-1);
	if (!fill_formatted_x(formatted_x, n, format, format_lst))
		return (-1);
	print_formatted_x(formatted_x, format_lst);
	if (format_lst->width > (int)ft_strlen(formatted_x))
		len = format_lst->width;
	else
		len = ft_strlen(formatted_x);
	free(formatted_x);
	return (len);
}
