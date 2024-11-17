/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpwi <lpwi@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:36:34 by lpwi              #+#    #+#             */
/*   Updated: 2024/11/17 14:36:39 by lpwi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/** pwd **/
/* take no options.
   output the current path, terminated with a newline. */
void	display_pwd(void)
{
	char	cwd[PATH_MAX];

	if(getcwd(cwd, sizeof(cwd)))
		ft_putendl_fd(cwd, 1);
}
