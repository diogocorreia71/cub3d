/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:54:02 by jmarinho          #+#    #+#             */
/*   Updated: 2024/06/25 15:58:44 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_player_movements(t_game *cub3d)
{
	t_player	*player;
	t_pos		new_pos;

	/* printf("dir.x %f\n", cub3d->player.direction.x);
	printf("dir.y %f\n", cub3d->player.direction.y);
	printf("plane.x %f\n", cub3d->player.plane.pos.x);
	printf("plane.y %f\n", cub3d->player.plane.pos.y); */
	player = &cub3d->player;
	new_pos.x = 0;
	new_pos.y = 0;
	if (cub3d->key == W || cub3d->key == S)
	{	
		new_pos.x = player->pos.x + player->direction.x * SPEED * player->movement.y;
		new_pos.y = player->pos.y + player->direction.y * SPEED * player->movement.y;
		if (cub3d->map.game_map[(int)new_pos.y][(int)new_pos.x] == '0')
			player->pos = new_pos;
	}
	else if (cub3d->key == A || cub3d->key == D)
	{
		new_pos.x = player->pos.x + player->plane.pos.x * SPEED * player->movement.x;
		new_pos.y = player->pos.y + player->plane.pos.y * SPEED * player->movement.x;
		if (cub3d->map.game_map[(int)new_pos.y][(int)new_pos.x] == '0')
			player->pos = new_pos;
	}
	ft_rotate(cub3d);
}

void	ft_rotate(t_game *cub3d)
{
	t_player *player;
	double	angle;
	double	old_dir_x;
	double	old_plane_x;

	player = &cub3d->player;
	old_dir_x = player->direction.x;
	old_plane_x = player->plane.pos.x;
	if (cub3d->key == LEFT || cub3d->key == RIGHT)
	{
		angle = player->angle * (double)(3.1415 / 180);
		player->direction.x =  (player->direction.x * cos(angle) - player->direction.y * sin(angle));
		player->direction.y = (old_dir_x * sin(angle) + player->direction.y * cos(angle));
		player->plane.pos.x =  (player->plane.pos.x * cos(angle) - player->plane.pos.y * sin(angle));
		player->plane.pos.y =  (old_plane_x * sin(angle) + player->plane.pos.y * cos(angle));	
	}
}
