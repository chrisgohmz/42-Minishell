/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpwi <lpwi@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:36:42 by lpwi              #+#    #+#             */
/*   Updated: 2024/11/17 14:36:44 by lpwi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/** unset **/
/* undefine a variable during the program execution. */
void	unset_env(char *var)
{
	if(ft_isalnum(var) && var_index(var) != -1)
		free(__environ[var_index(var)]);
}
