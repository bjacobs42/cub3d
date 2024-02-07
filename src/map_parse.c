/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_parse.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: maxb <maxb@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/26 12:27:02 by maxb          #+#    #+#                 */
/*   Updated: 2024/02/07 13:48:21 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	last_position(char *str)
{
	char	*set;
	int		lastPos;

	set = "10NEWS";
	lastPos = -1;
	for (int i = 0; str[i] != '\0'; ++i)
	{
		if (ft_strchr(set, str[i]))
			lastPos = i + 1;
	}
	return (lastPos);
}

int	check_map_length(t_param *p)
{
	int		length;
	t_node	*tmp;

	length = 0;
	tmp = p->tmp_map;
	while (tmp)
	{
		length = last_position(tmp->line);
		if (length > p->map.length)
			p->map.length = length;
		tmp = tmp->next;
	}
	return (p->map.length);
}

char	*read_new_line(char *sub, t_param *p)
{
	char	*line;

	free(sub);
	line = get_next_line(p->fd);
	if (!line)
		return (NULL);
	if (line[ft_strlen(line) - 1] == '\n')
		sub = ft_substr(line, 0, ft_strlen(line) - 1);
	else
		sub = ft_substr(line, 0, ft_strlen(line));
	if (!sub)
		return (NULL);
	if (!sub[0])
		return (free(sub), free(line), NULL);
	free(line);
	return (sub);
}

int	fill_map(char *sub, t_param *p)
{
	t_map	*map;

	map = &p->map;
	while (sub)
	{
		if (insert_node(&p->tmp_map, sub))
			return (ft_free_lst(p->tmp_map), free(sub), ERROR);
		sub = read_new_line(sub, p);
	}
	map->length = check_map_length(p);
	normalize_map(p);
	p->map.map = get_map(p);
	if (!p->map.map)
		return (ERROR);
	p->map.flood = get_map(p);
	if (!p->map.flood)
		return (ERROR);
	ft_free_lst(p->tmp_map);
	p->tmp_map = NULL;
	p->map.height = ft_2d_arrlen(p->map.map);
	p->end_map_parse = true;
	return (OK);
}

int	parse_map(char *line, t_param *p)
{
	char	**split;
	char	*sub;

	if (get_str_without_nl(line, &sub))
		return (OK);
	split = ft_split(sub, ' ');
	if (!split)
		return (free(line), free(sub), ERROR);
	// this will exit when catching a parameter like NO,SO,EA,WE,F,C
	if (get_type_no_space(split[0]) != ERROR)
		return (ft_2dfree(split), OK);
	if (full_textures(p) || fill_map(sub, p))
		return (ft_2dfree(split), ERROR);
	ft_2dfree(split);
	// Check below means the map have been filled,so we can check the validity of the map
	if (p->map.map)
		return (check_map(p));
	return (OK);
}
