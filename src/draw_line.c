/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 18:07:29 by bjacobs           #+#    #+#             */
/*   Updated: 2024/02/06 18:33:55 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_pixel(mlx_image_t *img, int x, int y, uint32_t color)
{
	if (x < img->width && x >= 0 && y < img->height && y >= 0)
		mlx_put_pixel(img, x, y, color);
}

static void	init_data(int *delta, int *step, t_vec2 p1, t_vec2 p2)
{
	delta[0] = abs((int)p2.x - (int)p1.x);
	delta[1] = abs((int)p2.y - (int)p1.y);
	if (p1.x < p2.x)
		step[0] = 1;
	else
		step[0] = -1;
	if (p1.y < p2.y)
		step[1] = 1;
	else
		step[1] = -1;
}

static int	out_of_bounds(t_vec2 p1, t_vec2 p2)
{
	return ((p1.x > WIDTH - 1 && p2.x > WIDTH - 1) || (p1.x < 0 && p2.x < 0)
		|| (p1.y > HEIGHT - 1 && p2.y > HEIGHT - 1) || (p1.y < 0 && p2.y < 0));
}

void	draw_line(mlx_image_t *img, t_vec2 p1, t_vec2 p2, uint32_t color)
{
	int	delta[2];
	int	step[2];
	int	err[2];

	init_data(delta, step, p1, p2);
	err[0] = delta[0] - delta[1];
	put_pixel(img, p1.x, p1.y, color);
	while (((int)p1.x != (int)p2.x || (int)p1.y != (int)p2.y)
		&& !out_of_bounds(p1, p2))
	{
		err[1] = 2 * err[0];
		if (err[1] >= -delta[1])
		{
			err[0] -= delta[1];
			p1.x += step[0];
		}
		if (err[1] <= delta[0])
		{
			err[0] += delta[0];
			p1.y += step[1];
		}
		put_pixel(img, p1.x, p1.y, color);
	}
}
