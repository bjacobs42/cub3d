/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/07 13:43:37 by mbernede      #+#    #+#                 */
/*   Updated: 2024/02/16 18:30:51 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	get_color_wall(mlx_texture_t *texture, uint32_t pos_x,
		uint32_t pos_y, double shade)
{
	uint32_t	pixel_index;
	t_ucolor	c;

	pixel_index = (pos_y * texture->width + pos_x) * texture->bytes_per_pixel;
	c.r = texture->pixels[pixel_index] * shade;
	c.g = texture->pixels[pixel_index + 1] * shade;
	c.b = texture->pixels[pixel_index + 2] * shade;
	return (ft_pixel(c.r, c.g, c.b, 255));
}

void	fill_wall(t_wall *wall, t_dda dda, int tex_width)
{
	float	tex_offset;

	wall->height = (HEIGHT * 10) / dda.ray.length;
	wall->py_step = (float)tex_width / (float)wall->height;
	if (wall->height > HEIGHT)
	{
		tex_offset = (float)(wall->height - HEIGHT) / 2.0f;
		wall->height = HEIGHT;
	}
	else
		tex_offset = 0;
	wall->shade = exp(-0.015 * dda.ray.length);
	if (dda.ray.type == X)
		wall->percent_x = pourcentage_of(dda.ray.hit.x);
	else
	{
		wall->percent_x = pourcentage_of(dda.ray.hit.y);
		wall->shade *= .8;
	}
	if (dda.ray.side == S_SOUTH || dda.ray.side == S_EAST)
		wall->percent_x = 0.99999999999f - wall->percent_x;
	if (wall->percent_x < 0)
		wall->percent_x = 0;
	wall->percent_x *= (float)tex_width;
	wall->percent_y = tex_offset * wall->py_step;
}

void	draw_wall(t_param *param, t_dda dda)
{
	t_wall	wall;
	int		ymap;
	int		y;

	y = 0;
	fill_wall(&wall, dda, param->textures[dda.ray.side]->width);
	while (y < wall.height)
	{
		ymap = y + HALF_HEIGHT - (wall.height >> 1);
		mlx_put_pixel(param->reality, dda.rays, ymap,
			get_color_wall(param->textures[dda.ray.side],
				wall.percent_x, wall.percent_y, wall.shade));
		wall.percent_y += wall.py_step;
		++y;
	}
}
