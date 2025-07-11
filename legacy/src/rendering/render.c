/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bjacobs <bjacobs@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/16 18:40:18 by bjacobs       #+#    #+#                 */
/*   Updated: 2024/02/16 18:43:46 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_img(mlx_image_t *img)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	pixels;

	i = 0;
	j = 3;
	pixels = img->width * img->height;
	while (i < pixels)
	{
		if (img->pixels[j])
			img->pixels[j] = 0;
		++i;
		j += 4;
	}
}

void	draw_square(int size, t_vec2 p, mlx_image_t *img, uint32_t color)
{
	int	x;
	int	y;

	x = 0;
	while (x < size)
	{
		y = 0;
		while (y < size)
		{
			if (p.x + y < img->width && p.x + y >= 0 && p.y + x < img->height
				&& p.y + x >= 0)
				mlx_put_pixel(img, p.x + y, p.y + x, color);
			++y;
		}
		++x;
	}
}

void	draw_minimap(t_map map)
{
	t_vec2	p;

	p.y = 0;
	while (p.y < map.height)
	{
		p.x = 0;
		while (p.x < map.length)
		{
			if (map.map[(int)p.y][(int)p.x] == '1')
				draw_square(CELL_SIZE, v2_mult(p, CELL_SIZE), map.minimap,
					WALL_COL);
			else if (ft_strchr("0NWSE", map.map[(int)p.y][(int)p.x]))
				draw_square(CELL_SIZE, v2_mult(p, CELL_SIZE), map.minimap,
					map.floor_color);
			else if (ft_strchr("DO", map.map[(int)p.y][(int)p.x]))
				draw_square(CELL_SIZE, v2_mult(p, CELL_SIZE), map.minimap,
					DOOR_COL);
			else
				draw_square(CELL_SIZE, v2_mult(p, CELL_SIZE), map.minimap,
					0x00000000);
			++p.x;
		}
		++p.y;
	}
}

void	render(t_param *p)
{
	t_dda			data;
	float			camera_x;
	static float	x_step = 1.0f / WIDTH;

	data.rays = 0;
	camera_x = -.5f;
	clear_img(p->reality);
	draw_minimap(p->map);
	while (data.rays < WIDTH)
	{
		data.angle = fix_angle(p->player.angle + atan2(camera_x, FOV));
		dda(&data, &p->player, p->map, "1D");
		draw_wall(p, data);
		draw_line(p->map.minimap, data.ray.hit,
			p->player.pos, RAY_COL);
		data.rays++;
		camera_x += x_step;
	}
	draw_square(4, v2_sub(p->player.pos, v2_new(2, 2)),
		p->map.minimap, PLAYER_COL);
}
