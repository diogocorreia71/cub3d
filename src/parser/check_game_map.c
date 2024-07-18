/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_game_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diodos-s <diodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:27:25 by jmarinho          #+#    #+#             */
/*   Updated: 2024/07/18 12:15:57 by diodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_other_if(t_game *cub3d, int pos, int i, int k)
{
	if (pos == 'N' || pos == 'S' || pos == 'E'
		|| pos == 'W')
	{
		cub3d->map.player_count++;
		if (cub3d->map.player_count != 1)
			ft_perror("Error\nMore than one player on game map\n",
				cub3d);
		else
		{
			cub3d->player.tile = cub3d->map.game_map[i][k];
			cub3d->player.pos.x = k;
			cub3d->player.pos.y = i;
			cub3d->map.game_map[i][k] = '0';
		}
	}
}

void	ft_check_invalid_chars(t_game *cub3d)
{
	int		i;
	int		k;
	int		pos;

	i = -1;
	while (cub3d->map.game_map[++i])
	{
		k = -1;
		while (cub3d->map.game_map[i][++k])
		{
			pos = cub3d->map.game_map[i][k];
			if (pos != '0' && pos != '1' && pos != 'N' && pos != 'S'
				&& pos != 'E' && pos != 'W' && pos != ' ' && pos != '\t'
				&& pos != '\n')
				ft_perror("Error\nInvalid characters on game map\n", cub3d);
			ft_other_if(cub3d, pos, i, k);
		}
	}
	if (cub3d->map.player_count == 0)
		ft_perror("Error\nNo player on game map\n", cub3d);
}

void	ft_check_game_map(t_game *cub3d)
{
	ft_check_invalid_chars(cub3d);
	ft_get_rows(cub3d);
	ft_get_cols(cub3d);
	ft_create_flood_map(cub3d);
	ft_flood_fill(cub3d->player.pos.x, cub3d->player.pos.y, cub3d);
	ft_free_dp((void **)cub3d->map.flood_map);
}
