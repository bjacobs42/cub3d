/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   valid_input.c                                      :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/07 13:34:11 by mbernede      #+#    #+#                 */
/*   Updated: 2024/02/15 20:47:54 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// check if exist and we can open it
int	open_file(char *arg)
{
	int		fd;

	fd = open(arg, O_RDONLY);
	if (fd > 0)
		return (fd);
	return (0);
}

// used to check if file end with .cub
bool	endswith(char *str, char *suffix)
{
	int	str_len;
	int	suffix_len;

	str_len = ft_strlen(str);
	suffix_len = ft_strlen(suffix);
	if (str_len < suffix_len)
		return (false);
	return (ft_strncmp(str + (str_len - suffix_len), suffix, suffix_len) == 0);
}

bool	check_file(char *arg)
{
	if (!open_file(arg))
		return (printf(ERR_FILE), ERROR);
	if (!endswith(arg, ".cub"))
		return (printf(ERR_NOCUB), ERROR);
	return (OK);
}
