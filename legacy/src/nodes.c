/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nodes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/07 13:38:12 by mbernede      #+#    #+#                 */
/*   Updated: 2024/02/07 13:38:59 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_our_lst_size(t_node *lst)
{
	int		count;
	t_node	*current;

	count = 0;
	current = lst;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}

void	ft_free_lst(t_node *head)
{
	t_node	*next;
	t_node	*current;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current->line);
		free(current);
		current = next;
	}
}

t_node	*create_node(char *line)
{
	t_node	*new_node;

	new_node = (t_node *)ft_calloc(1, sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->line = ft_strdup(line);
	if (!new_node->line)
		return (ft_free_node(new_node), NULL);
	return (new_node);
}

int	insert_node(t_node **head, char *line)
{
	t_node	*new_node;
	t_node	*current;

	new_node = create_node(line);
	if (!new_node)
		return (ft_free_lst(*head), ERROR);
	if (*head == NULL)
	{
		*head = new_node;
		return (OK);
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = new_node;
	return (OK);
}

void	print_list(t_node *head)
{
	t_node	*current;

	current = head;
	while (current != NULL)
	{
		printf("%s\n", current->line);
		current = current->next;
	}
}
