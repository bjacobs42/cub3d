/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_back_bonus.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: maxb <maxb@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 16:21:43 by mbernede      #+#    #+#                 */
/*   Updated: 2023/11/25 19:38:39 by maxb          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstadd_back(t_list **lst, t_list *n)
{
	t_list	*ptrlst;

	if (!lst || !n)
		return ;
	if (*lst)
	{
		ptrlst = ft_lstlast(*lst);
		ptrlst->next = n;
	}
	else
		*lst = n;
}
