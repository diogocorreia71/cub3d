/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:00:08 by jmarinho          #+#    #+#             */
/*   Updated: 2024/06/20 15:22:55 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_end_game(t_game *cub3d)
{
	int	i;

	i = -1;
	while (++i < 5)
		mlx_destroy_image(cub3d->lib, cub3d->sprite[i].img.img_ptr);
	mlx_clear_window(cub3d->lib, cub3d->window);
	mlx_destroy_window(cub3d->lib, cub3d->window);
	ft_free_dp((void **)cub3d->map.file_map);
	mlx_destroy_display(cub3d->lib);
	free(cub3d->lib);
	exit(EXIT_SUCCESS);
}

int	ft_keypress(int keycode, t_game *cub3d)
{
	t_player	*player;

	player = &cub3d->player;
	if (keycode == ESC)
		ft_end_game(cub3d);
	else if (keycode == W)
		player->movement.y = 1;
	else if (keycode == S)
		player->movement.y = -1;
	else if (keycode == A)
		player->movement.x = -1;
	else if (keycode == D)
		player->movement.x = 1;
	else if (keycode == LEFT)
		player->angle = -1;
	else if (keycode == RIGHT)
		player->angle = 1;
	return (EXIT_SUCCESS);
}

int	ft_keyrelease(int keycode, t_player *player)
{
	if (keycode == W || keycode == S)
		player->movement.y = 0;
	else if (keycode == A || keycode == D)
		player->movement.x = 0;
	else if (keycode == LEFT || keycode == RIGHT)
		player->angle = 0;
	return (EXIT_SUCCESS);
}