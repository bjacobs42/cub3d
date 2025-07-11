/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_angle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 00:46:46 by bjacobs           #+#    #+#             */
/*   Updated: 2024/02/11 01:07:40 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	fix_angle(float angle)
{
	if (angle < 0)
		angle += TWO_PI;
	else if (angle > TWO_PI)
		angle -= TWO_PI;
	return (angle);
}
