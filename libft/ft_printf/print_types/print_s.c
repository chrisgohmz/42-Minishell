/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:00:49 by cgoh              #+#    #+#             */
/*   Updated: 2024/06/26 20:12:39 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	print_s(t_format *format_lst, char *str)
{
	char	*flags;
	int		width;
	int		precision;
	int		left;
	int		total_len;

	flags = format_lst->flags;
	width = format_lst->width;
	precision = format_lst->precision;
	left = 0;
	if (ft_strchr(flags, '-'))
		left = 1;
	total_len = print_formatted_s(str, width, precision, left);
	return (total_len);
}

int	print_formatted_s(char *str, int width, int precision, int left)
{
	char	*substr;
	int		total_len;
	int		substr_len;

	substr = get_substr(str, precision);
	if (!substr)
		return (-1);
	substr_len = (int)ft_strlen(substr);
	if (width > substr_len)
		total_len = width;
	else
		total_len = substr_len;
	while (!left && width-- > substr_len)
		ft_putchar_fd(' ', 1);
	ft_putstr_fd(substr, 1);
	while (width-- > substr_len)
		ft_putchar_fd(' ', 1);
	free(substr);
	return (total_len);
}

char	*get_substr(char *str, int precision)
{
	char	*substr;

	if (!str)
	{
		substr = malloc((6 * (precision >= 6
						|| precision == -1) + 1) * sizeof(char));
		if (!substr)
			return (NULL);
		if (precision >= 6 || precision == -1)
			ft_strlcpy(substr, "(null)", 7);
		else
			substr[0] = '\0';
	}
	else
	{
		substr = ft_substr(str, 0, precision);
		if (!substr)
			return (NULL);
	}
	return (substr);
}
