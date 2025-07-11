/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: maxb <maxb@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/07 13:40:11 by mbernede      #+#    #+#                 */
/*   Updated: 2024/02/21 17:11:41 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Check textures exists and can be opened then assign them to the structure
int	side_textures(int type, char *arg, t_param *p)
{
	int	fd;

	fd = open_file(arg);
	if (fd < 1)
		return (printf(ERR_OPEN_TEXTURES), ERROR);
	close(fd);
	if (fill_texture(type, p, arg))
		return (printf("Cub3d: Error filling textures\n"), ERROR);
	return (OK);
}

// remove the \n then check if empty
// next, make a string with the rest of the output then fill
int	check_line(char *line, t_param *param)
{
	char	*sub;
	int		type;
	char	**split;

	if (get_str_without_nl(line, &sub))
		return (OK);
	split = ft_split(sub, ' ');
	if (!split)
		return (printf(ERR_MLC), free(sub), ERROR);
	type = get_type_no_space(split[0]);
	if (type == ERROR)
		return (ft_2dfree(split), free(sub), printf(ERR_TYPE), ERROR);
	sub = get_str_no_space(sub);
	if (!sub)
		return (ft_2dfree(split), printf(ERR_MLC), ERROR);
	if ((type == FLOOR || type == CEILING) && floor_ceiling(type, sub, param))
		return (ft_2dfree(split), free(sub), ERROR);
	else if (type >= NORTH && side_textures(type, sub, param))
		return (ft_2dfree(split), free(sub), ERROR);
	free(sub);
	ft_2dfree(split);
	return (OK);
}

// will check if we need to fill map, in case it start filling the map
// the program won't run the checkline. Parsemap itself will check
// that there is nothing after the parsing of the map
int	parse_file(char *arg, t_param *p)
{
	char	*line;

	p->fd = open_file(arg);
	if (p->fd <= 0)
		return (ERROR);
	line = get_next_line(p->fd);
	if (!line)
		return (printf(ERR_EMPTY_MAP), ERROR);
	while (line)
	{
		if (!p->end_map_parse && parse_map(line, p))
			return (free(line), printf(ERR_FILL_MAP), close(p->fd), ERROR);
		if (!p->end_map_parse && check_line(line, p))
			return (free(line), printf(ERR_FILE_DATA), close(p->fd), ERROR);
		free(line);
		line = get_next_line(p->fd);
	}
	close(p->fd);
	if (!p->map.map)
		return (printf(ERR_NO_MAP), ERROR);
	return (OK);
}
