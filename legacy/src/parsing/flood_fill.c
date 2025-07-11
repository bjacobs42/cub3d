/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flood_fill.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/07 13:49:55 by mbernede      #+#    #+#                 */
/*   Updated: 2024/02/07 14:23:22 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define ANSI_RED "\x1b[31m"
#define ANSI_GREEN "\x1b[32m"
#define ANSI_WHITE "\x1b[37m"
#define ANSI_RESET "\x1b[0m"

void	print_flood(t_map map)
{
	int	y;
	int	x;

	y = 0;
	printf("\n");
	while (y < map.height)
	{
		x = 0;
		while (x < map.length)
		{
			if (map.flood[y][x] == '1')
				printf(ANSI_RED "■" ANSI_RESET);
			else if (map.flood[y][x] == '9')
				printf(ANSI_GREEN "■" ANSI_RESET);
			else if (map.flood[y][x] == '0')
				printf(ANSI_WHITE "■" ANSI_RESET);
			else
				printf("■");
			++x;
		}
		printf("\n");
		++y;
	}
}

int	flood_fill(t_map map, int x, int y)
{
	int	r;

	r = 0;
	if (x < 0 || x >= map.length || y < 0 || y >= map.height
		|| map.flood[y][x] == ' ')
	{
		return (ERROR);
	}
	if (map.flood[y][x] == '1' || map.flood[y][x] == '9')
		return (OK);
	map.flood[y][x] = '9';
	r += flood_fill(map, x, y - 1);
	r += flood_fill(map, x, y + 1);
	r += flood_fill(map, x + 1, y);
	r += flood_fill(map, x - 1, y);
	return (r);
}
