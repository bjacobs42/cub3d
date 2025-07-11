/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   struct.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/16 18:50:26 by mbernede      #+#    #+#                 */
/*   Updated: 2024/02/21 17:28:20 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "../MLX42/include/MLX42/MLX42.h"

typedef enum s_xy
{
	X,
	Y
}			t_xy;

typedef enum s_sides
{
	S_NORTH,
	S_SOUTH,
	S_EAST,
	S_WEST,
	S_DOOR,
	S_KEY,
	S_DOOR_OPEN
}					t_sides;

typedef struct s_wall
{
	int				height;
	float			percent_y;
	float			percent_x;
	float			py_step;
	double			shade;
}					t_wall;

typedef struct s_ucolor
{
	uint32_t		r;
	uint32_t		g;
	uint32_t		b;
}					t_ucolor;

typedef struct s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct s_vec2
{
	double			x;
	double			y;
}					t_vec2;

typedef struct s_ray_data
{
	t_vec2			hit;
	t_vec2			ray_step;
	t_vec2			origin;
	float			length;
	enum s_xy		type;
	enum s_sides	side;
}	t_ray;

typedef struct s_dda_data
{
	t_ray	ray;
	float	angle;
	int		rays;
}			t_dda;

typedef struct s_player
{
	t_vec2		pos;
	t_vec2		delta;
	float		angle;
}			t_player;

typedef struct s_map
{
	char			**flood;
	char			**map;
	int				length;
	int				height;
	int				tile_size;
	uint32_t		floor_color;
	uint32_t		ceil_color;
	mlx_image_t		*minimap;
}					t_map;

typedef struct s_node
{
	char			*line;
	struct s_node	*next;
}					t_node;

typedef struct s_param
{
	t_color			floor;
	t_color			ceiling;
	mlx_texture_t	*textures[5];
	xpm_t			*xpms[5];
	int				fd;
	bool			end_map_parse;
	t_node			*tmp_map;
	t_map			map;
	t_player		player;
	mlx_t			*mlx;
	mlx_image_t		*reality;
	mlx_image_t		*background;
}					t_param;

#endif
