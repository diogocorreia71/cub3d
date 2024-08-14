/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diodos-s <diodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:33:43 by jmarinho          #+#    #+#             */
/*   Updated: 2024/07/23 14:14:39 by diodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_init_player_pos(t_game *cub3d)
{
	int	dir;

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
	cub3d->player.plane.pos.x = -cub3d->player.direction.y * 0.66;
	cub3d->player.plane.pos.y = cub3d->player.direction.x;
	cub3d->key = 0;
}

int	ft_make_game(t_game *cub3d)
{
	if (cub3d->key)
		ft_player_movements(cub3d);
	ft_image_buffer(cub3d);
	ft_raycast(cub3d);
	return (EXIT_SUCCESS);
}
