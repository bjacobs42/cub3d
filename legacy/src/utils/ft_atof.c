/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atof.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/07 13:22:35 by mbernede      #+#    #+#                 */
/*   Updated: 2024/02/07 14:02:22 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_num(double *result, double *fraction, int *sign)
{
	*result = 0;
	*fraction = 0.1;
	*sign = 1;
}

void	is_negative(int *sign, char **nptr)
{
	if (**nptr == '-' && (*nptr)++)
		*sign = -1;
	else if (**nptr == '+')
		(*nptr)++;
}

// makes the number a double
double	ft_atof(char *nptr)
{
	double	result;
	double	fraction;
	int		sign;

	init_num(&result, &fraction, &sign);
	while (ft_isspace(*nptr))
		nptr++;
	is_negative(&sign, &nptr);
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	if (*nptr == '.')
	{
		nptr++;
		while (*nptr >= '0' && *nptr <= '9')
		{
			result += (*nptr - '0') * fraction;
			fraction /= 10.0;
			nptr++;
		}
	}
	return (result * sign);
}
