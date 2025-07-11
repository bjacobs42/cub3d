/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/07 13:17:52 by mbernede      #+#    #+#                 */
/*   Updated: 2024/02/07 15:29:13 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// check in case of a format rgb like : 255,240,0
int	nb_or_comma(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]) && s[i] != ',')
			return (ERROR);
		i++;
	}
	return (OK);
}

//!add overflow checks
int	to_decimal(char *s, double *f)
{
	*f = ft_atof(s);
	return (OK);
}

// fill the colors could be changed with structure to be more easy to read
int	is_colors(char *s, int *r, int *g, int *b)
{
	char	**split;

	if (ft_strlen(s) > 11 || nb_or_comma(s))
		return (ERROR);
	split = ft_split(s, ',');
	if (!split)
		return (ERROR);
	if (ft_2d_arrlen(split) != 3)
		return (ft_2dfree(split), ERROR);
	*r = ft_atoi(split[0]);
	*g = ft_atoi(split[1]);
	*b = ft_atoi(split[2]);
	if (*r > 255 || *g > 255 || *b > 255)
		return (ft_2dfree(split), ERROR);
	return (ft_2dfree(split), OK);
}

char	*concatenate_strings(char **strings, int num_string)
{
	int		total_len;
	char	*result;
	int		index;
	int		i;

	total_len = 0;
	i = -1;
	while (++i < num_string)
		total_len += ft_strlen(strings[i]);
	result = (char *)malloc(total_len + 1);
	if (!result)
		return (printf(ERR_MLC), NULL);
	index = 0;
	i = -1;
	while (++i < num_string)
		index += ft_strlcpy(result + index, strings[i], total_len + 1
				- index);
	return (result);
}

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}
