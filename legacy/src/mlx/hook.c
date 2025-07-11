/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hook.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/07 13:32:59 by mbernede      #+#    #+#                 */
/*   Updated: 2024/02/21 17:17:03 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	action_key_down(mlx_t *mlx)
{
	return (mlx_is_key_down(mlx, MLX_KEY_W) || mlx_is_key_down(mlx, MLX_KEY_S)
		|| mlx_is_key_down(mlx, MLX_KEY_A) || mlx_is_key_down(mlx, MLX_KEY_D)
		|| mlx_is_key_down(mlx, MLX_KEY_E));
}

void	cursor_hook(double xpos, double ypos, void *param)
{
	static bool	active = false;
	double		dx;
	t_param		*p;

	p = (t_param *)param;
	if (mlx_is_key_down(p->mlx, MLX_KEY_LEFT_ALT))
	{
		if (active)
		{
			active = false;
			mlx_set_cursor_mode(p->mlx, MLX_MOUSE_NORMAL);
		}
		return ;
	}
	mlx_set_mouse_pos(p->mlx, 512, 256);
	dx = xpos - 512.0;
	change_player_angle(&p->player, dx * MOUSESPEED, p->mlx->delta_time);
	if (!active)
	{
		active = true;
		(void)ypos ;
		mlx_set_cursor_mode(p->mlx, MLX_MOUSE_HIDDEN);
	}
}

void	my_hook(void *param)
{
	t_param	*p;

	p = param;
	if (mlx_is_key_down(p->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(p->mlx);
	if (mlx_is_key_down(p->mlx, MLX_KEY_W))
		move_player(p, false, -1, p->mlx->delta_time);
	if (mlx_is_key_down(p->mlx, MLX_KEY_S))
		move_player(p, false, 1, p->mlx->delta_time);
	if (mlx_is_key_down(p->mlx, MLX_KEY_D))
		move_player(p, true, -1, p->mlx->delta_time);
	if (mlx_is_key_down(p->mlx, MLX_KEY_A))
		move_player(p, true, 1, p->mlx->delta_time);
	if (mlx_is_key_down(p->mlx, MLX_KEY_LEFT))
		change_player_angle(&p->player, -1 * TURNSPEED, p->mlx->delta_time);
	if (mlx_is_key_down(p->mlx, MLX_KEY_RIGHT))
		change_player_angle(&p->player, 1 * TURNSPEED, p->mlx->delta_time);
	if (mlx_is_key_down(p->mlx, MLX_KEY_E))
		open_door(&p->player, &p->map);
	render(param);
}
