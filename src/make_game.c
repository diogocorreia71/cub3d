/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:33:43 by jmarinho          #+#    #+#             */
/*   Updated: 2024/06/20 15:39:08 by jmarinho         ###   ########.fr       */
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
	cub3d->player.plane.x = 0;
    cub3d->player.plane.y = 0.66;
}

int	ft_make_game(t_game *cub3d)
{
	int pixelX;
	int	pixelY;

	pixelX = 0;
	start_image_buffer(cub3d);
	while(pixelX++ < WIDTH)
	{
		pixelY = 300;
		while (pixelY++ < HEIGHT)
		{
			pixel_put(&cub3d->buffer, pixelX, pixelY, 0xFF0000);
		}
	}
	mlx_put_image_to_window(cub3d->lib, cub3d->window, cub3d->buffer.img_ptr, 0, 0);
	return (EXIT_SUCCESS);
}
