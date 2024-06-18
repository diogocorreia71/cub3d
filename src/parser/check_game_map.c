/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_game_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:27:25 by jmarinho          #+#    #+#             */
/*   Updated: 2024/06/17 14:37:16 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_get_rows(t_game *cub3d)
{
	int	i;

	i = -1;
	cub3d->map.x = 0;
	if (!cub3d->map.game_map)
		return ;
	while (cub3d->map.game_map[++i])
		cub3d->map.x++;
}

void	ft_get_cols(t_game *cub3d)
{
	int	i;

	i = -1;
	cub3d->map.y = 0;
	if (!cub3d->map.game_map)
		return ;
	while (cub3d->map.game_map[++i])
	{
		if ((int)ft_strlen(cub3d->map.game_map[i]) > cub3d->map.y)
			cub3d->map.y = ft_strlen(cub3d->map.game_map[i]);
	}
	cub3d->map.y--;
}

void	ft_check_invalid_chars(t_game *cub3d)
{
	int		i;
	int		k;
	int	pos;

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
				ft_perror("ERROR\nInvalid characters on game map\n", cub3d);
			else if (pos == 'N' || pos == 'S' || pos == 'E'
				|| pos == 'W')
			{
				cub3d->map.player_count++;
				if (cub3d->map.player_count != 1)
					ft_perror("ERROR\nMore than one player on game map\n", cub3d);
				else
				{
					cub3d->map.player_pos.x = i;
					cub3d->map.player_pos.y = k;
				}
			}
		}
	}
}

void	ft_flood_fill(int x, int y, t_game *cub3d)
{
	if (cub3d->map.flood_map[x][y] == '1')
		return ;
	else if (cub3d->map.flood_map[x][y] != '0' && cub3d->map.flood_map[x][y] != '1'
		&& cub3d->map.flood_map[x][y] != 'N' && cub3d->map.flood_map[x][y] != 'S'
		&& cub3d->map.flood_map[x][y] != 'E' && cub3d->map.flood_map[x][y] != 'W')
	{
		ft_free_dp((void **)cub3d->map.flood_map);
		ft_perror("ERROR\nMap is open\n", cub3d);
	}
	cub3d->map.flood_map[x][y] = '1';
	ft_flood_fill(x + 1, y, cub3d);
	ft_flood_fill(x, y + 1, cub3d);
	ft_flood_fill(x - 1, y, cub3d);
	ft_flood_fill(x, y - 1, cub3d);
}

void	ft_create_flood_map(t_game *cub3d)
{
	int	i;

	i = -1;
	cub3d->map.flood_map = malloc(sizeof(char *) * (cub3d->map.x + 1));
	if (!cub3d->map.flood_map)
		ft_perror ("ERROR\nMalloc for cub3d->map.flood_map failed\n", cub3d);
	while (cub3d->map.game_map[++i])
		cub3d->map.flood_map[i] = ft_strdup(cub3d->map.game_map[i]);
	cub3d->map.flood_map[i] = NULL;
}

void	ft_check_game_map(t_game *cub3d)
{
	cub3d->map.player_count = 0;
	ft_check_invalid_chars(cub3d);
	ft_get_rows(cub3d);
	ft_get_cols(cub3d);
	ft_create_flood_map(cub3d);
	ft_flood_fill(cub3d->map.player_pos.x, cub3d->map.player_pos.y, cub3d);
	ft_free_dp((void **)cub3d->map.flood_map);
}
