/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_game_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:27:25 by jmarinho          #+#    #+#             */
/*   Updated: 2024/06/17 12:16:14 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_get_rows(t_mlx *mlx)
{
	int	i;

	i = -1;
	mlx->map.x = 0;
	if (!mlx->map.game_map)
		return ;
	while (mlx->map.game_map[++i])
		mlx->map.x++;
}

void	ft_get_cols(t_mlx *mlx)
{
	int	i;

	i = -1;
	mlx->map.y = 0;
	if (!mlx->map.game_map)
		return ;
	while (mlx->map.game_map[++i])
	{
		if ((int)ft_strlen(mlx->map.game_map[i]) > mlx->map.y)
			mlx->map.y = ft_strlen(mlx->map.game_map[i]);
	}
	mlx->map.y--;
}

void	ft_check_invalid_chars(t_mlx *mlx)
{
	int		i;
	int		k;
	int	pos;

	i = -1;
	while (mlx->map.game_map[++i])
	{
		k = -1;
		while (mlx->map.game_map[i][++k])
		{
			pos = mlx->map.game_map[i][k];
			if (pos != '0' && pos != '1' && pos != 'N' && pos != 'S'
				&& pos != 'E' && pos != 'W' && pos != ' ' && pos != '\t'
				&& pos != '\n')
				ft_perror("ERROR\nInvalid characters on game map\n", mlx);
			else if (pos == 'N' || pos == 'S' || pos == 'E'
				|| pos == 'W')
			{
				mlx->map.player_count++;
				if (mlx->map.player_count != 1)
					ft_perror("ERROR\nMore than one player on game map\n", mlx);
				else
				{
					mlx->map.player_pos.x = i;
					mlx->map.player_pos.y = k;
				}
			}
		}
	}
}

void	ft_flood_fill(int x, int y, t_mlx *mlx)
{
	if (mlx->map.flood_map[x][y] == '1')
		return ;
	else if (mlx->map.flood_map[x][y] != '0' && mlx->map.flood_map[x][y] != '1'
		&& mlx->map.flood_map[x][y] != 'N' && mlx->map.flood_map[x][y] != 'S'
		&& mlx->map.flood_map[x][y] != 'E' && mlx->map.flood_map[x][y] != 'W')
	{
		ft_free_dp((void **)mlx->map.flood_map);
		ft_perror("ERROR\nMap is open\n", mlx);
	}
	mlx->map.flood_map[x][y] = '1';
	ft_flood_fill(x + 1, y, mlx);
	ft_flood_fill(x, y + 1, mlx);
	ft_flood_fill(x - 1, y, mlx);
	ft_flood_fill(x, y - 1, mlx);
}

void	ft_create_flood_map(t_mlx *mlx)
{
	int	i;

	i = -1;
	mlx->map.flood_map = malloc(sizeof(char *) * (mlx->map.x + 1));
	if (!mlx->map.flood_map)
		ft_perror ("ERROR\nMalloc for mlx->map.flood_map failed\n", mlx);
	while (mlx->map.game_map[++i])
		mlx->map.flood_map[i] = ft_strdup(mlx->map.game_map[i]);
	mlx->map.flood_map[i] = NULL;
}

void	ft_check_game_map(t_mlx *mlx)
{
	mlx->map.player_count = 0;
	ft_check_invalid_chars(mlx);
	ft_get_rows(mlx);
	ft_get_cols(mlx);
	ft_create_flood_map(mlx);
	ft_flood_fill(mlx->map.player_pos.x, mlx->map.player_pos.y, mlx);
	ft_free_dp((void **)mlx->map.flood_map);
}
