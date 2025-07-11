/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dda.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bjacobs <bjacobs@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/16 18:40:37 by bjacobs       #+#    #+#                 */
/*   Updated: 2024/02/16 18:44:00 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

//angle < PI is looking up
// else looking down
int	init_xray(t_ray *ray, t_vec2 origin, float angle)
{
	float	tangent;

	if (angle == 0 || angle == PI)
		return (ray->length = 100000, EXIT_FAILURE);
	tangent = 1.0f / tan(angle);
	ray->origin = origin;
	ray->type = X;
	if (angle < PI)
	{
		ray->hit.y = (((int)ray->origin.y >> 3) << 3) - 0.0001;
		ray->ray_step.y = -CELL_SIZE;
		ray->side = S_NORTH;
	}
	else
	{
		ray->hit.y = (((int)ray->origin.y >> 3) << 3) + CELL_SIZE;
		ray->ray_step.y = CELL_SIZE;
		ray->side = S_SOUTH;
	}
	ray->hit.x = (ray->hit.y - ray->origin.y) * tangent + ray->origin.x;
	ray->ray_step.x = ray->ray_step.y * tangent;
	return (EXIT_SUCCESS);
}

// angle < HALF_PI || angle > THIRD_PI is looking left
// else right
int	init_yray(t_ray *ray, t_vec2 origin, float angle)
{
	float	tangent;

	if (angle == HALF_PI || angle == THIRD_PI)
		return (ray->length = 100000, EXIT_FAILURE);
	tangent = tan(angle);
	ray->origin = origin;
	ray->type = Y;
	if (angle < HALF_PI || angle > THIRD_PI)
	{
		ray->hit.x = (((int)ray->origin.x >> 3) << 3) - 0.0001;
		ray->ray_step.x = -CELL_SIZE;
		ray->side = S_WEST;
	}
	else
	{
		ray->hit.x = (((int)ray->origin.x >> 3) << 3) + CELL_SIZE;
		ray->ray_step.x = CELL_SIZE;
		ray->side = S_EAST;
	}
	ray->hit.y = (ray->hit.x - ray->origin.x) * tangent + ray->origin.y;
	ray->ray_step.y = ray->ray_step.x * tangent;
	return (EXIT_SUCCESS);
}

void	cast_ray(t_ray *ray, t_map map, float player_angle, char *hit_condition)
{
	int	mapx;
	int	mapy;

	mapx = (int)ray->hit.x >> 3;
	mapy = (int)ray->hit.y >> 3;
	while (mapy < map.height && mapx < map.length && mapy >= 0 && mapx >= 0
		&& !ft_strchr(hit_condition, map.map[mapy][mapx]))
	{
		ray->hit.y += ray->ray_step.y;
		ray->hit.x += ray->ray_step.x;
		mapx = (int)ray->hit.x >> 3;
		mapy = (int)ray->hit.y >> 3;
	}
	if (mapy < map.height && mapx < map.length && mapy >= 0 && mapx >= 0
		&& (map.map[mapy][mapx] == 'D' || map.map[mapy][mapx] == 'O'))
	{
		ray->side = S_DOOR;
	}
	ray->length = -((ray->hit.x - ray->origin.x) * cos(player_angle) \
			+ (ray->hit.y - ray->origin.y) * sin(player_angle));
}

void	dda(t_dda *data, t_player *player, t_map map, char *hit_condition)
{
	t_ray	ray;

	if (!init_xray(&data->ray, player->pos, data->angle))
		cast_ray(&data->ray, map, player->angle, hit_condition);
	if (!init_yray(&ray, player->pos, data->angle))
		cast_ray(&ray, map, player->angle, hit_condition);
	if (data->ray.length > ray.length)
		data->ray = ray;
}
