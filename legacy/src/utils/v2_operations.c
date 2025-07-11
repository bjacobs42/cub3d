/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v2_operations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 01:22:10 by bjacobs           #+#    #+#             */
/*   Updated: 2023/12/25 20:46:51 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

t_vec2	v2_new(double x, double y)
{
	t_vec2	v2;

	v2.x = x;
	v2.y = y;
	return (v2);
}

t_vec2	v2_mult(t_vec2 v2, double multiplier)
{
	v2.x *= multiplier;
	v2.y *= multiplier;
	return (v2);
}

t_vec2	v2_add(t_vec2 v2, t_vec2 add)
{
	v2.x += add.x;
	v2.y += add.y;
	return (v2);
}

t_vec2	v2_sub(t_vec2 v2, t_vec2 sub)
{
	v2.x -= sub.x;
	v2.y -= sub.y;
	return (v2);
}
