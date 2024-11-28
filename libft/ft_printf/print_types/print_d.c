/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:39:08 by cgoh              #+#    #+#             */
/*   Updated: 2024/11/29 02:29:58 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static char	*malloc_str_d(int n, char *flags, int precision)
{
	int		len;
	char	*n_str;
	char	*formatted_d;
	int		extra;

	n_str = ft_itoa(n);
	if (!n_str)
		return (NULL);
	len = ft_strlen(n_str) - (n == 0 && precision == 0)
		+ ((ft_strchr(flags, ' ')
				|| ft_strchr(flags, '+')) && n >= 0);
	extra = ((n < 0)
			|| ft_strchr(flags, ' ') || ft_strchr(flags, '+'));
	if ((precision + extra) > len)
		len = precision + extra;
	free(n_str);
	formatted_d = malloc((len + 1) * sizeof(char));
	if (!formatted_d)
		return (NULL);
	ft_memset(formatted_d, 1, len);
	formatted_d[len] = '\0';
	return (formatted_d);
}

static int	fill_formatted_d(char *formatted_d, t_format *format_lst, int n)
{
	char	*n_str;
	int		i;
	int		n_start;

	n_str = ft_itoa(n);
	if (!n_str)
		return (0);
	i = 0;
	if (n < 0)
	{
		formatted_d[i++] = '-';
		n_str++;
	}
	else if (ft_strchr(format_lst->flags, '+'))
		formatted_d[i++] = '+';
	else if (ft_strchr(format_lst->flags, ' '))
		formatted_d[i++] = ' ';
	n_start = ft_strlen(formatted_d) - ft_strlen(n_str);
	while (i < n_start)
		formatted_d[i++] = '0';
	formatted_d[i] = '\0';
	ft_strlcat(formatted_d, n_str, n_start + ft_strlen(n_str) + 1);
	free(n_str - (n < 0));
	return (1);
}

static void	print_formatted_d(char *formatted_d, t_format *format_lst)
{
	int		left;
	char	*flags;
	int		width;
	int		sign_first;

	left = 0;
	flags = format_lst->flags;
	width = format_lst->width;
	if (ft_strchr(flags, '-'))
		left = 1;
	sign_first = (ft_strchr(" +-", formatted_d[0])
			&& format_lst->precision < 0
			&& (ft_strchr(flags, '0')));
	if (sign_first)
		ft_putchar_fd(formatted_d[0], format_lst->fd);
	while (!left && width-- > (int)ft_strlen(formatted_d))
	{
		if (format_lst->precision < 0 && ft_strchr(flags, '0'))
			ft_putchar_fd('0', format_lst->fd);
		else
			ft_putchar_fd(' ', format_lst->fd);
	}
	ft_putstr_fd(formatted_d + sign_first, format_lst->fd);
	while (width-- > (int)ft_strlen(formatted_d))
		ft_putchar_fd(' ', format_lst->fd);
}

int	print_d(t_format *format_lst, int n)
{
	char	*flags;
	char	*formatted_d;
	int		len;

	flags = format_lst->flags;
	formatted_d = malloc_str_d(n, flags, format_lst->precision);
	if (!formatted_d)
		return (-1);
	if (!fill_formatted_d(formatted_d, format_lst, n))
		return (-1);
	print_formatted_d(formatted_d, format_lst);
	if (format_lst->width > (int)ft_strlen(formatted_d))
		len = format_lst->width;
	else
		len = ft_strlen(formatted_d);
	free(formatted_d);
	return (len);
}
