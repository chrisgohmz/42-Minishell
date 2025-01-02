/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:49:14 by cgoh              #+#    #+#             */
/*   Updated: 2025/01/03 04:01:18 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#define MAX_FLAGS	5

static int	print_replacement(t_format *format_lst, char specifier,
	va_list va_ptr)
{
	int		len;

	if (specifier == 'c')
		len = print_char(format_lst, va_arg(va_ptr, int));
	else if (specifier == 's')
		len = print_s(format_lst, va_arg(va_ptr, char *));
	else if (specifier == 'p')
		len = print_p(format_lst, va_arg(va_ptr, void *));
	else if (specifier == 'd' || specifier == 'i')
		len = print_d(format_lst, va_arg(va_ptr, int));
	else if (specifier == 'u')
		len = print_u(format_lst, va_arg(va_ptr, unsigned int));
	else if (specifier == 'x')
		len = print_x(format_lst, va_arg(va_ptr, unsigned int), 'x');
	else if (specifier == 'X')
		len = print_x(format_lst, va_arg(va_ptr, unsigned int), 'X');
	else if (specifier == '%')
		len = print_pct(format_lst);
	else
		len = -2;
	return (len);
}

static int	parse_flags(t_format *format_lst, int *i, const char *format)
{
	char	*flags;
	char	possible_flags[MAX_FLAGS + 1];
	int		flag_num;

	flags = malloc((MAX_FLAGS + 1) * sizeof(char));
	if (!flags)
		return (0);
	ft_bzero(flags, MAX_FLAGS + 1);
	ft_strlcpy(possible_flags, "-+ 0#", sizeof(possible_flags));
	flag_num = 0;
	while (ft_strchr(possible_flags, format[*i]))
	{
		if (!ft_strchr(flags, format[*i]))
		{
			flags[flag_num] = format[*i];
			flag_num++;
		}
		(*i)++;
	}
	format_lst->flags = flags;
	return (1);
}

static int	parse_width(t_format *format_lst, int *i, const char *format)
{
	int		len;
	char	*width_str;

	len = 0;
	while (ft_isdigit(format[*i + len]))
		len++;
	if (!len)
	{
		format_lst->width = 0;
		return (1);
	}
	width_str = ft_substr(format, *i, len);
	if (!width_str)
		return (0);
	format_lst->width = ft_atoi(width_str);
	free(width_str);
	*i += len;
	return (1);
}

static int	parse_precision(t_format *format_lst, int *i, const char *format)
{
	int		len;
	char	*precision_str;

	len = 0;
	if (format[(*i)] != '.')
	{
		format_lst->precision = -1;
		return (1);
	}
	(*i)++;
	while (ft_isdigit(format[*i + len]))
		len++;
	if (!len)
	{
		format_lst->precision = 0;
		return (1);
	}
	precision_str = ft_substr(format, *i, len);
	if (!precision_str)
		return (0);
	format_lst->precision = ft_atoi(precision_str);
	free(precision_str);
	*i += len;
	return (1);
}

int	parse_str(va_list va_ptr, int *i, const char *format, t_format *format_lst)
{
	int			str_len;
	int			start;

	if (format[*i] != '%')
	{
		ft_putchar_fd(format[*i], format_lst->fd);
		return (1);
	}
	if (!format[(*i) + 1])
		return (-1);
	(*i)++;
	start = *i;
	if (!parse_flags(format_lst, i, format)
		|| !parse_width(format_lst, i, format)
		|| !parse_precision(format_lst, i, format))
		return (-1);
	str_len = print_replacement(format_lst, format[*i], va_ptr);
	if (str_len == -2)
		str_len = print_specifier(format, start, *i, format_lst);
	free(format_lst->flags);
	return (str_len);
}
