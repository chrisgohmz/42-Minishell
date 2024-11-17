/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpwi <lpwi@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:36:11 by lpwi              #+#    #+#             */
/*   Updated: 2024/11/17 14:36:13 by lpwi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/** env **/
/* output a list of all environment variabless.
   environment variables are dynamic values that affect the behaviour of proccesses on a system. They are available to the shell and any child processes spawned from the shell. */
void	display_env(void)
{
	int	i;

	i = 0;
	while(__environ[i])
	{
		ft_putendl_fd(_environ[i], 1);
		i++;
	}
}
