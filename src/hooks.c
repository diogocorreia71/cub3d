/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diodos-s <diodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:00:08 by jmarinho          #+#    #+#             */
/*   Updated: 2024/07/10 13:55:48 by diodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_end_game(t_game *cub3d)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < 6)
		free(cub3d->map.config_map[i]);
	while (i++ < cub3d->map.total_lines)
		free(cub3d->map.game_map[++j]);
	free (cub3d->map.game_map);
	i = -1;
	while (++i < 4)
		mlx_destroy_image(cub3d->lib, cub3d->sprite[i].image.img_ptr);
	mlx_clear_window(cub3d->lib, cub3d->window);
	mlx_destroy_window(cub3d->lib, cub3d->window);
	ft_free_dp((void **)cub3d->map.file_map);
	mlx_destroy_display(cub3d->lib);
	free(cub3d->lib);
	exit(EXIT_SUCCESS);
}

int	ft_keypress(int keycode, t_game *cub3d)
{
	cub3d->key = keycode;
	if (cub3d->key == ESC)
		ft_end_game(cub3d);
	if (cub3d->key == W)
		cub3d->player.movement.y = 1;
	if (cub3d->key == S)
		cub3d->player.movement.y = -1;
	if (cub3d->key == A)
		cub3d->player.movement.x = -1;
	if (cub3d->key == D)
		cub3d->player.movement.x = 1;
	if (cub3d->key == LEFT)
		cub3d->player.angle = -1;
	if (cub3d->key == RIGHT)
		cub3d->player.angle = 1;
	return (EXIT_SUCCESS);
}

int	ft_keyrelease(int keycode, t_game *cub3d)
{
	cub3d->key = keycode;
	if (cub3d->key == W || cub3d->key == S)
		cub3d->player.movement.y = 0;
	if (cub3d->key == A || cub3d->key == D)
		cub3d->player.movement.x = 0;
	if (cub3d->key == LEFT || cub3d->key == RIGHT)
		cub3d->player.angle = 0;
	return (EXIT_SUCCESS);
}
