/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 19:13:05 by cgoh              #+#    #+#             */
/*   Updated: 2024/06/26 20:12:11 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	print_char(t_format *format_lst, char c)
{
	char	*flags;
	int		width;
	int		precision;
	int		left;

	flags = format_lst->flags;
	width = format_lst->width;
	precision = format_lst->precision;
	left = 0;
	if (ft_strchr(flags, '-'))
		left = 1;
	print_formatted_char(c, width, left);
	if (width > 0)
		return (width);
	return (1);
}

void	print_formatted_char(char c, int width, int left)
{
	while (!left && width-- > 1)
		ft_putchar_fd(' ', 1);
	ft_putchar_fd(c, 1);
	while (width-- > 1)
		ft_putchar_fd(' ', 1);
}
