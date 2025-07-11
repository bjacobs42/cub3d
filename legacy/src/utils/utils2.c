/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: maxb <maxb@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/07 15:34:19 by mbernede      #+#    #+#                 */
/*   Updated: 2024/02/15 03:02:46 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	pourcentage_of(float coordinate)
{
	return ((fmodf(coordinate, CELL_SIZE)) / (float)CELL_SIZE);
}

char	*ft_strchr_nolast(const char *s, int c)
{
	char	*ptr;

	ptr = (char *)s;
	while (*ptr)
	{
		if (*ptr == (char)c)
			return (ptr);
		ptr++;
	}
	return (NULL);
}

void	print_all_ray(t_ray *ray)
{
	printf("ray origin x: %f, y: %f\n", ray->origin.x, ray->origin.y);
	printf("ray hit x: %f, y: %f\n", ray->hit.x, ray->hit.y);
	printf("ray hit x: %f, y: %f\n", pourcentage_of(ray->hit.x),
		pourcentage_of(ray->hit.y));
	printf("ray ray_step x: %f, y: %f\n", ray->ray_step.x, ray->ray_step.y);
	printf("ray length: %f\n", ray->length);
	printf("ray side: %d\n", ray->side);
}
