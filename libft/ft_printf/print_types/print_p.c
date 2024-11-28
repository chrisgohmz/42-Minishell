/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:39:08 by cgoh              #+#    #+#             */
/*   Updated: 2024/11/29 02:30:12 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static char	*malloc_str_p(void *p, char *flags, int precision)
{
	int		len;
	char	*p_str;
	char	*formatted_p;
	int		extra;
	int		null_p;

	p_str = ft_ptoa(p);
	if (!p_str)
		return (NULL);
	extra = (ft_strchr(flags, ' ') || ft_strchr(flags, '+'));
	null_p = (ft_strncmp(p_str, "(nil)", 6) == 0);
	len = ft_strlen(p_str) + (extra + 2) * !null_p;
	if ((precision + extra + 2) > len)
		len = precision + extra + 2;
	free(p_str);
	formatted_p = malloc((len + 1) * sizeof(char));
	if (!formatted_p)
		return (NULL);
	ft_memset(formatted_p, 1 + null_p, len);
	formatted_p[len] = '\0';
	return (formatted_p);
}

static int	fill_formatted_p(char *formatted_p, t_format *format_lst, void *p)
{
	char	*p_str;
	int		i;
	int		p_start;

	p_str = ft_ptoa(p);
	if (!p_str)
		return (0);
	i = 0;
	if (ft_strchr(format_lst->flags, '+'))
		formatted_p[i++] = '+';
	else if (ft_strchr(format_lst->flags, ' '))
		formatted_p[i++] = ' ';
	formatted_p[i++] = '0';
	formatted_p[i++] = 'x';
	p_start = ft_strlen(formatted_p) - ft_strlen(p_str);
	while (i < p_start)
		formatted_p[i++] = '0';
	formatted_p[i] = '\0';
	ft_strlcat(formatted_p, p_str, p_start + ft_strlen(p_str) + 1);
	free(p_str);
	return (1);
}

static void	print_formatted_p(char *formatted_p, t_format *format_lst)
{
	int		left;
	int		sign_first;
	int		width;

	left = (ft_strchr(format_lst->flags, '-') && 1 == 1);
	width = format_lst->width;
	sign_first = (ft_strchr(" +-", formatted_p[0]) && format_lst->precision < 0
			&& ft_strncmp(formatted_p, "(nil)", 6) != 0);
	if (sign_first)
	{
		ft_putchar_fd(formatted_p[0], format_lst->fd);
		ft_putchar_fd('0', format_lst->fd);
		ft_putchar_fd('x', format_lst->fd);
	}
	while (!left && width-- > (int)ft_strlen(formatted_p))
	{
		if (format_lst->precision < 0 && ft_strchr(format_lst->flags, '0'))
			ft_putchar_fd('0', format_lst->fd);
		else
			ft_putchar_fd(' ', format_lst->fd);
	}
	ft_putstr_fd(formatted_p + 3 * sign_first, format_lst->fd);
	while (width-- > (int)ft_strlen(formatted_p))
		ft_putchar_fd(' ', format_lst->fd);
}

int	print_p(t_format *format_lst, void *p)
{
	char	*flags;
	char	*formatted_p;
	int		len;

	flags = format_lst->flags;
	formatted_p = malloc_str_p(p, flags, format_lst->precision);
	if (!formatted_p)
		return (-1);
	if (formatted_p[0] == 2)
		ft_strlcpy(formatted_p, "(nil)", 6);
	else if (!fill_formatted_p(formatted_p, format_lst, p))
		return (-1);
	print_formatted_p(formatted_p, format_lst);
	if (format_lst->width > (int)ft_strlen(formatted_p))
		len = format_lst->width;
	else
		len = ft_strlen(formatted_p);
	free(formatted_p);
	return (len);
}
