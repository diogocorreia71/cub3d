/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:28:30 by jmarinho          #+#    #+#             */
/*   Updated: 2024/07/25 16:05:39 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include <assert.h>
# include <stdbool.h>
# include <math.h>

# define NO 0
# define SO 1
# define EA 2
# define WE 3
# define F 	4
# define C 	5

# define WIDTH 800
# define HEIGHT 600
# define SPRITE_SIZE 64
# define SPEED 0.025
# define ROTATION_SPEED 0.6
# define BUFFER_DISTANCE 0.1

# define PI 3.14159265358

# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363

typedef struct s_pos
{
	double		x;
	double		y;
}	t_pos;

typedef struct s_rays
{
	t_pos		direction;
	t_pos		delta;
	t_pos		intersection;
	t_pos		map_mov;
	bool		hit_vertical;
	double		perp_wall_dist;
}	t_rays;

typedef struct s_plane
{
	t_pos		pos;
	double		angle;
}	t_plane;

typedef struct s_player
{
	char		tile;
	t_pos		pos;
	t_pos		direction;
	t_pos		movement;
	t_plane		plane;
	int			int_pos_x;
	int			int_pos_y;
	double		angle;
}	t_player;

typedef struct s_map
{
	int			x;
	int			y;
	int			total_lines;
	int			lines_to_map;
	int			player_count;
	char		**file_map;
	char		*config_map[6];
	char		**game_map;
	char		**flood_map;
	bool		no_flag;
	bool		so_flag;
	bool		ea_flag;
	bool		we_flag;
	bool		f_flag;
	bool		c_flag;
	char		*clean_line;
}	t_map;

typedef struct s_image
{
	void		*img_ptr;
	char		*address;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}	t_image;

typedef struct s_img_info
{
	double		line_height;
	int			draw_start;
	int			draw_end;
	double		pos_texture;
	double		scale;
	int			tex_x;
}	t_img_info;

typedef struct s_sprite
{
	t_image		image;
	int			height;
	int			width;
	int			index;
}	t_sprite;

typedef struct s_game
{
	t_map		map;
	char		*file;
	void		*lib;
	void		*window;
	t_sprite	sprite[4];
	t_sprite	texture;
	t_player	player;
	t_image		image;
	t_img_info	img_info;
	int			c_color;
	int			f_color;
	t_rays		ray;
	int			key;
}	t_game;

// Map
void		ft_check_b4_init(char **av, t_game *cub3d);
void		ft_check_game_map(t_game *cub3d);
void		ft_copy_config_map(t_game *cub3d);
void		ft_copy_game_map(t_game *cub3d);
int			ft_check_all_config_flags(t_game *cub3d);
void		ft_count_map_lines(t_game *cub3d);
int			ft_check_if_line_is_blank(char *line);

//Copy_config_map_aux
int			ft_check_for_configs(t_game *cub3d, char *line);

//Flood_fill_and_counters
void		ft_create_flood_map(t_game *cub3d);
void		ft_flood_fill(int x, int y, t_game *cub3d);
void		ft_get_rows(t_game *cub3d);
void		ft_get_cols(t_game *cub3d);

//Parser_utils
void		ft_print_map(char **map);
void		ft_free_stack_array(void **arg);
void		ft_check_rgb(t_game *cub3d);
void		ft_free_dp(void **arg);
void		ft_perror(char *msg, t_game *cub3d);

//Sprite_utils
t_sprite	ft_get_sprite_info(t_game *cub3d, char *texture);
void		ft_texture_calculus(t_game *cub3d);

//Hooks
int			ft_end_game(t_game *cub3d);
int			ft_keypress(int keycode, t_game *cub3d);
int			ft_keyrelease(int keycode, t_game *cub3d);

//Make_game
void		ft_init_player_pos(t_game *cub3d);
int			ft_make_game(t_game *cub3d);

//Img_buffer
void		ft_image_buffer(t_game *cub3d);

//Img
void		pixel_put(t_image *img, int pixelX, int pixelY, int color);

//Raycasting
void		ft_raycast(t_game *cub3d);
void		ft_sprites(t_game *cub3d, int i);
void		ft_color(t_game *cub3d, int i, char flag);

//Movements
void		ft_player_movements(t_game *cub3d);
int			ft_is_valid_move_with_buffer(t_game *cub3d, t_pos new_pos);
int			ft_check_buffer_zone(t_game *cub3d, t_pos new_pos);
void		ft_rotate(t_game *cub3d);

#endif