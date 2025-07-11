/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/07 13:33:19 by mbernede      #+#    #+#                 */
/*   Updated: 2024/02/15 21:09:03 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_background(mlx_image_t *background, t_param *param)
{
	int		x;
	int		y;
	double	shade;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		shade = (double)y / HEIGHT;
		while (x < WIDTH)
		{
			if (y < HEIGHT >> 1)
				mlx_put_pixel(background, x, y, param->map.ceil_color);
			else
				mlx_put_pixel(background, x, y,
					ft_pixel(param->floor.r * shade, param->floor.g * shade,
						param->floor.b * shade, 255));
			++x;
		}
		++y;
	}
}

int	init_images(t_param *param)
{
	param->background = mlx_new_image(param->mlx, WIDTH, HEIGHT);
	if (!param->background)
		return (ERROR);
	param->reality = mlx_new_image(param->mlx, WIDTH, HEIGHT);
	if (!param->reality)
		return (ERROR);
	param->map.minimap = mlx_new_image(param->mlx, param->map.length
			* CELL_SIZE, param->map.height * CELL_SIZE);
	if (!param->map.minimap)
		return (ERROR);
	return (OK);
}

int	start(t_param *param)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	param->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	if (!param->mlx)
		return (ERROR);
	if (init_images(param))
		return (mlx_close_window(param->mlx), printf(ERR_IMG_CREA), ERROR);
	init_player(param->map, &param->player);
	draw_background(param->background, param);
	mlx_set_mouse_pos(param->mlx, 512, 256);
	render(param);
	if (mlx_image_to_window(param->mlx, param->background, 0, 0) == -1
		|| mlx_image_to_window(param->mlx, param->reality, 0, 0) == -1
		|| mlx_image_to_window(param->mlx, param->map.minimap, 0, 0) == -1)
	{
		mlx_close_window(param->mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	mlx_cursor_hook(param->mlx, cursor_hook, param);
	mlx_loop_hook(param->mlx, my_hook, param);
	mlx_loop(param->mlx);
	mlx_terminate(param->mlx);
	return (OK);
}
