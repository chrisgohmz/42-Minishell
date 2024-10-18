/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:40:34 by cgoh              #+#    #+#             */
/*   Updated: 2024/05/20 16:53:35 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	write_num(unsigned int num, int fd)
{
	char	c;

	if (!num)
		return ;
	write_num(num / 10, fd);
	c = (num % 10) + '0';
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	num;

	if (n < 0)
	{
		write(fd, "-", 1);
		num = (unsigned int)-n;
		write_num(num, fd);
	}
	else if (n == 0)
		write(fd, "0", 1);
	else
	{
		num = (unsigned int)n;
		write_num(num, fd);
	}
}
