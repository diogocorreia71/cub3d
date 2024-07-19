/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diodos-s <diodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:54:02 by jmarinho          #+#    #+#             */
/*   Updated: 2024/07/19 10:00:00 by diodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_player_movements(t_game *cub3d)
{
	t_player	*player;
	t_pos		new_pos;

	player = &cub3d->player;
	new_pos.x = 0;
	new_pos.y = 0;
	new_pos.x = player->pos.x + player->direction.x
		* SPEED * player->movement.y;
	new_pos.y = player->pos.y + player->direction.y
		* SPEED * player->movement.y;
	if (ft_is_valid_move_with_buffer(cub3d, new_pos))
		player->pos = new_pos;
	new_pos.x = player->pos.x + player->plane.pos.x
		* SPEED * player->movement.x;
	new_pos.y = player->pos.y + player->plane.pos.y
		* SPEED * player->movement.x;
	if (ft_is_valid_move_with_buffer(cub3d, new_pos))
		player->pos = new_pos;
	ft_rotate(cub3d);
}

int	ft_is_valid_move_with_buffer(t_game *cub3d, t_pos new_pos)
{
	int	new_x;
	int	new_y;

	new_x = (int)new_pos.x;
	new_y = (int)new_pos.y;
	if (new_x < 0 || new_y < 0 || new_y >= cub3d->map.total_lines
		|| new_x >= (int)ft_strlen(cub3d->map.game_map[new_y]))
		return (0);
	if (cub3d->map.game_map[new_y][new_x] != '0')
		return (0);
	if (!ft_check_buffer_zone(cub3d, new_pos))
		return (0);
	return (1);
}

int	ft_check_buffer_zone(t_game *cub3d, t_pos new_pos)
{
	double	angle;
	double	check_x;
	double	check_y;
	int		map_x;
	int		map_y;

	angle = 0;
	if (angle < 2 * PI)
	{
		check_x = new_pos.x + cos(angle) * BUFFER_DISTANCE;
		check_y = new_pos.y + sin(angle) * BUFFER_DISTANCE;
		map_x = (int)check_x;
		map_y = (int)check_y;
		if (map_x < 0 || map_y < 0 || map_y >= cub3d->map.total_lines
			|| map_x >= (int)ft_strlen(cub3d->map.game_map[map_y]))
			return (0);
		if (cub3d->map.game_map[map_y][map_x] != '0')
			return (0);
		angle += PI / 8;
	}
	return (1);
}

void	ft_rotate(t_game *cub3d)
{
	t_player	*player;
	double		angle;
	double		old_dir_x;
	double		old_plane_x;

	player = &cub3d->player;
	old_dir_x = player->direction.x;
	old_plane_x = player->plane.pos.x;
	if (cub3d->key == LEFT || cub3d->key == RIGHT)
	{
		angle = player->angle * (double)(PI / 180)*ROTATION_SPEED;
		player->direction.x = (player->direction.x * cos(angle)
				- player->direction.y * sin(angle));
		player->direction.y = (old_dir_x * sin(angle)
				+ player->direction.y * cos(angle));
		player->plane.pos.x = (player->plane.pos.x * cos(angle)
				- player->plane.pos.y * sin(angle));
		player->plane.pos.y = (old_plane_x * sin(angle)
				+ player->plane.pos.y * cos(angle));
	}
}
