/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gets.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: maxb <maxb@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/07 13:43:24 by mbernede      #+#    #+#                 */
/*   Updated: 2024/02/21 17:05:48 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// The map is transformed from a linked list to a char **
char	**get_map(t_param *p)
{
	t_node	*current;
	char	**map;
	int		i;

	current = p->tmp_map;
	i = 0;
	map = (char **)malloc((ft_our_lst_size(current) + 1) * sizeof(char *));
	if (!map)
		return (printf(ERR_MLC), NULL);
	while (current)
	{
		map[i] = ft_strdup(current->line);
		current = current->next;
		++i;
	}
	map[i] = NULL;
	return (map);
}

int	get_type(char *line)
{
	if (!ft_strncmp("F ", line, 2))
		return (FLOOR);
	if (!ft_strncmp("C ", line, 2))
		return (CEILING);
	if (!ft_strncmp("NO ", line, 3))
		return (NORTH);
	if (!ft_strncmp("SO ", line, 3))
		return (SOUTH);
	if (!ft_strncmp("EA ", line, 3))
		return (EAST);
	if (!ft_strncmp("WE ", line, 3))
		return (WEST);
	return (ERROR);
}

int	get_type_no_space(char *line)
{
	int	i;

	if (!line)
		return (ERROR);
	i = ft_strlen(line);
	if (i == 1 && !ft_strncmp("F", line, 1))
		return (FLOOR);
	if (i == 1 && !ft_strncmp("C", line, 1))
		return (CEILING);
	if (i == 2 && !ft_strncmp("NO", line, 2))
		return (NORTH);
	if (i == 2 && !ft_strncmp("SO", line, 2))
		return (SOUTH);
	if (i == 2 && !ft_strncmp("EA", line, 2))
		return (EAST);
	if (i == 2 && !ft_strncmp("WE", line, 2))
		return (WEST);
	if (i == 4 && !ft_strncmp("DOOR", line, 4))
		return (DOOR);
	return (ERROR);
}

int	get_char_start(t_map map, int *y, int *x)
{
	*y = 0;
	while (*y < map.height)
	{
		*x = 0;
		while (*x < map.length)
		{
			if (ft_strchr("NSEW", map.map[*y][*x]))
				return (OK);
			++(*x);
		}
		++(*y);
	}
	return (ERROR);
}
