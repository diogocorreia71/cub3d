/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:28:30 by jmarinho          #+#    #+#             */
/*   Updated: 2024/06/20 15:31:27 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
//# include "vector2D.h"
# include <assert.h>
# include <stdbool.h>
# include <math.h>

# define NO 0
# define SO 1
# define EA 2
# define WE 3
# define F 	4
# define C 	5

# define HEIGHT 600
# define WIDTH 600
# define FOV 90

# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363

typedef struct s_pos
{
	double	x;
	double	y;
}	t_pos;

typedef struct s_player
{
	char	tile;
	t_pos	pos;
	t_pos	direction;
	t_pos	plane;
	t_pos	movement;
	double	fov;
	double	angle;
}	t_player;

typedef struct s_map
{
	int		x;
	int		y;
	int		total_lines;
	int		lines_to_map;
	int		player_count;
	char	**file_map;
	char	*config_map[6];
	char	**game_map;
	char	**flood_map;
	bool	no_flag;
	bool	so_flag;
	bool	ea_flag;
	bool	we_flag;
	bool	f_flag;
	bool	c_flag;
}	t_map;

typedef struct s_image
{
	void	*img_ptr;
	char	*address;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_sprite
{
	t_image	img;
	int		height;
	int		width;
}	t_sprite;

typedef struct s_ray
{
	t_pos	dir;
	t_pos	delta;
	t_pos	side_d;
	t_pos	step;
}	t_ray;

typedef struct s_game
{
	t_map		map;
	char		*file;
	void		*lib;
	void		*window;
	t_sprite	sprite[6];
	t_player	player;
	t_image		buffer;
	int			c_color;
	int			f_color;
}	t_game;

// Map
void		ft_check_b4_init(int ac, char **av, t_game *cub3d);
void		ft_check_game_map(t_game *cub3d);
void		ft_copy_config_map(t_game *cub3d);
void		ft_copy_game_map(t_game *cub3d);
int			ft_check_all_config_flags(t_game *cub3d);
void		ft_count_map_lines(t_game *cub3d);
int			ft_check_if_line_is_blank(char *line);

//Parser_utils
void		ft_print_map(char **map);
void		ft_free_stack_array(void **arg);
void		ft_check_rgb(t_game *cub3d);
void		ft_free_dp(void **arg);
void		ft_perror(char *msg, t_game *cub3d);

//Sprite_utils
t_sprite    ft_get_sprite_info(t_game *cub3d, char *texture);

//Hooks
int			ft_end_game(t_game *cub3d);
int			ft_keypress(int keycode, t_game *cub3d);
int			ft_keyrelease(int keycode, t_player *player);

//Make_game
void		ft_init_player_pos(t_game *cub3d);
int			ft_make_game(t_game *cub3d);

//Img_buffer
void		start_image_buffer(t_game *cub3d);

//Img
void	pixel_put(t_image *img, int pixelX, int pixelY, int color);

#endif