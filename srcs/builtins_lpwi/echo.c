/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpwi <lpwi@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:36:05 by lpwi              #+#    #+#             */
/*   Updated: 2024/11/17 14:36:07 by lpwi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/** echo **/
/* outputs the args separated by spaces, terminated with newline.
   if successful, return status is 0.
   if write error, return status is non 0.
   -n flag suppresses the newline */
   
void	echo(char **string)
{
	int	n_flag;
	int	args_count;

	n_flag = 0;
	args_count = 0;
	while(string[args_count])
		args_count++;
	if(ft_strcmp(string[1], "-n") == 0)
		n_flag = 1;
	if (args_count > 2)
	{
		while(string[j])
		{
			ft_putstr_fd(string[j], 1);
			if(string[j + 1] != "\0")
				ft_putstr_fd(" ", 1);
			j++;
		}
	}
	if (n_flag == 0)
		write(1, "\n", 1);	
}
