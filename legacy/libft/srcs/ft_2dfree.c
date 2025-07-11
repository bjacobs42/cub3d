/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_2dfree.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: maxb <maxb@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/25 20:06:24 by maxb          #+#    #+#                 */
/*   Updated: 2023/11/25 20:06:28 by maxb          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_2dfree(char **p_arr)
{
	int	i;

	i = 0;
	if (!p_arr)
		return ;
	while (p_arr[i] != NULL)
	{
		free(p_arr[i]);
		i++;
	}
	free(p_arr);
}
