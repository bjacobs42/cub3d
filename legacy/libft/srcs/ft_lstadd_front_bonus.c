/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_front_bonus.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: maxb <maxb@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 16:10:17 by mbernede      #+#    #+#                 */
/*   Updated: 2023/11/25 19:38:44 by maxb          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstadd_front(t_list **lst, t_list *n)
{
	if (*lst)
		n->next = *lst;
	*lst = n;
}
