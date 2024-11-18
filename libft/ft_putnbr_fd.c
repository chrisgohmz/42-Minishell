/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:40:34 by cgoh              #+#    #+#             */
/*   Updated: 2024/11/18 18:21:09 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	write_num(unsigned int num, int fd)
{
	char	c;
	ssize_t	chars;

	if (!num)
		return ;
	write_num(num / 10, fd);
	c = (num % 10) + '0';
	chars = write(fd, &c, 1);
	(void)chars;
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	num;
	ssize_t			chars;

	if (n < 0)
	{
		chars = write(fd, "-", 1);
		num = (unsigned int)-n;
		write_num(num, fd);
	}
	else if (n == 0)
		chars = write(fd, "0", 1);
	else
	{
		num = (unsigned int)n;
		write_num(num, fd);
	}
	(void)chars;
}
