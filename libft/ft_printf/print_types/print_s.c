/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:00:49 by cgoh              #+#    #+#             */
/*   Updated: 2024/11/29 02:31:55 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static char	*get_substr(char *str, int precision)
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

static int	print_formatted_s(char *str, t_format *format_lst, int left)
{
	char	*substr;
	int		total_len;
	int		substr_len;

	substr = get_substr(str, format_lst->precision);
	if (!substr)
		return (-1);
	substr_len = (int)ft_strlen(substr);
	if (format_lst->width > substr_len)
		total_len = format_lst->width;
	else
		total_len = substr_len;
	while (!left && format_lst->width-- > substr_len)
		ft_putchar_fd(' ', format_lst->fd);
	ft_putstr_fd(substr, format_lst->fd);
	while (format_lst->width-- > substr_len)
		ft_putchar_fd(' ', format_lst->fd);
	free(substr);
	return (total_len);
}

int	print_s(t_format *format_lst, char *str)
{
	char	*flags;
	int		left;
	int		total_len;

	flags = format_lst->flags;
	left = 0;
	if (ft_strchr(flags, '-'))
		left = 1;
	total_len = print_formatted_s(str, format_lst, left);
	return (total_len);
}
