/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:33:43 by jmarinho          #+#    #+#             */
/*   Updated: 2024/06/25 15:19:11 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    ft_init_player_pos(t_game *cub3d)
{
	int dir;

	dir = 1;
	if (cub3d->player.tile == 'N')
		cub3d->player.direction = (t_pos){0, -dir};
	else if (cub3d->player.tile == 'S')
		cub3d->player.direction = (t_pos){0, dir};
	else if (cub3d->player.tile == 'W')
		cub3d->player.direction = (t_pos){-dir, 0};
	else if (cub3d->player.tile == 'E')
		cub3d->player.direction = (t_pos){dir, 0};
	cub3d->player.movement = (t_pos){0, 0};
	cub3d->player.plane.angle = FOV / 90;
	cub3d->player.plane.pos.x = -cub3d->player.direction.y;
	cub3d->player.plane.pos.y = cub3d->player.direction.x;
}

int	ft_make_game(t_game *cub3d)
{
	ft_player_movements(cub3d);
	ft_image_buffer(cub3d);
	ft_raycast_by_lodev(cub3d);
	return (EXIT_SUCCESS);
}
