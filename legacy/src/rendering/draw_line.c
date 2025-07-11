/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 18:07:29 by bjacobs           #+#    #+#             */
/*   Updated: 2024/02/15 20:52:17 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color)
{
	if (x < img->width && y < img->height)
		mlx_put_pixel(img, x, y, color);
}

static void	init_data(int *delta, int *step, t_vec2 p1, t_vec2 p2)
{
	delta[X] = abs((int)p2.x - (int)p1.x);
	delta[Y] = abs((int)p2.y - (int)p1.y);
	if (p1.x < p2.x)
		step[X] = 1;
	else
		step[X] = -1;
	if (p1.y < p2.y)
		step[Y] = 1;
	else
		step[Y] = -1;
}

void	draw_line(mlx_image_t *img, t_vec2 p1, t_vec2 p2, uint32_t color)
{
	int	delta[2];
	int	step[2];
	int	err[2];

	init_data(delta, step, p1, p2);
	err[X] = delta[X] - delta[Y];
	put_pixel(img, p1.x, p1.y, color);
	while (((int)p1.x != (int)p2.x || (int)p1.y != (int)p2.y))
	{
		err[Y] = 2 * err[X];
		if (err[Y] >= -delta[Y])
		{
			err[X] -= delta[Y];
			if ((int)p1.x != (int)p2.x)
				p1.x += step[X];
		}
		if (err[Y] <= delta[X])
		{
			err[X] += delta[X];
			if ((int)p1.y != (int)p2.y)
				p1.y += step[Y];
		}
		put_pixel(img, p1.x, p1.y, color);
	}
}
