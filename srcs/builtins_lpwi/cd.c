/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpwi <lpwi@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:35:53 by lpwi              #+#    #+#             */
/*   Updated: 2024/11/17 14:35:57 by lpwi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/** cd **/
/* go to the defined directory.
   absolute path: start with the root directory and provide the full path or directory
   relative path: path to a file or directory that is relative to the current directory */
int	ft_cd(char *path)
{
	int	chdir_ret;

	chdir_ret = chdir(path);
	if(chdir_ret == 0)
		printf("cd successful.\n");
	else
		printf("cd failure.\n");
	return(chdir_ret);
}
