/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: maxb <maxb@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/07 13:43:17 by mbernede      #+#    #+#                 */
/*   Updated: 2024/02/21 17:33:18 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// this is made to free more easily in case of a parsing error
int	init_null(t_param *p)
{
	int	i;

	i = 0;
	while (i < 5)
		p->textures[i++] = NULL;
	p->ceiling.r = -1;
	p->ceiling.g = -1;
	p->ceiling.b = -1;
	p->floor.r = -1;
	p->floor.g = -1;
	p->floor.b = -1;
	p->end_map_parse = false;
	p->map.length = -1;
	p->map.height = 0;
	p->map.map = NULL;
	p->map.flood = NULL;
	p->tmp_map = NULL;
	p->reality = NULL;
	p->background = NULL;
	p->map.minimap = NULL;
	return (OK);
}

int	main(int argc, char **argv)
{
	t_param	param;

	if (argc != 2)
		return (printf(ERR_ARG), 1);
	if (init_null(&param))
		return (ERROR);
	if (check_file(argv[1]))
		return (clean_everything(&param), ERROR);
	if (parse_file(argv[1], &param))
		return (clean_everything(&param), ERROR);
	if (!search_in_map(&param, "D") && !param.textures[S_DOOR])
		return (clean_everything(&param), printf(ERR_NOTEXT), ERROR);
	if (start(&param))
		return (0);
	clean_everything(&param);
	return (0);
}
