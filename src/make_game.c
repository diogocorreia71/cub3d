/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:33:43 by jmarinho          #+#    #+#             */
/*   Updated: 2024/06/19 10:30:58 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    ft_player_pos_and_dir(t_game *cub3d)
{
	int dir;

	dir = 1;
	//player.pos = (t_pos){x, y};
	if (cub3d->player.tile == 'N')
		cub3d->player.direction = (t_pos){0, -dir};
	else if (cub3d->player.tile == 'S')
		cub3d->player.direction = (t_pos){0, dir};
	else if (cub3d->player.tile == 'W')
		cub3d->player.direction = (t_pos){-dir, 0};
	else if (cub3d->player.tile == 'E')
		cub3d->player.direction = (t_pos){dir, 0};
	cub3d->player.movement = (t_pos){0, 0};
	cub3d->player.plane.x = -cub3d->player.direction.y;
    cub3d->player.plane.y = cub3d->player.direction.x;
	cub3d->player.angle = 0.1;
	cub3d->player.fov = (double)FOV / 90;
}

void	ft_refresh_position(t_game *cub3d)
{
	cub3d->player.movement = (t_pos){0, 0};
	cub3d->player.angle = 0.1;
}

void	ft_make_game(t_game *cub3d)
{
	ft_refresh_position(cub3d);
	cub3d->buffer = start_image_buffer(cub3d->lib);
	ft_grua(cub3d);
	cub3d_destroy_image(cub3d->lib, cub3d->buffer.img_ptr);
}
