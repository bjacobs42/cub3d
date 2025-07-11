/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nodes2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/07 13:37:57 by mbernede      #+#    #+#                 */
/*   Updated: 2024/02/07 13:38:20 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_node(t_node *node)
{
	free(node->line);
	free(node);
}
