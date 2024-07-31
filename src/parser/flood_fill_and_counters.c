/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_and_counters.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diodos-s <diodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:27:25 by jmarinho          #+#    #+#             */
/*   Updated: 2024/07/31 10:46:15 by diodos-s         ###   ########.fr       */
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

void	ft_flood_fill(int x, int y, t_game *cub3d)
{
	t_map	*map;

	map = &cub3d->map;
	if (x < 0 || x >= map->y || y < 0 || y >= map->x)
	{
		ft_free_dp((void **)map->flood_map);
		ft_perror("Error\nMap is open\n", cub3d);
	}
	if (map->flood_map[y][x] == '1')
		return ;
	else if (map->flood_map[y][x] != '0' && map->flood_map[y][x] != 'N'
		&& map->flood_map[y][x] != 'S' && map->flood_map[y][x] != 'E'
		&& map->flood_map[y][x] != 'W')
	{
		ft_free_dp((void **)map->flood_map);
		ft_perror("Error\nMap is open\n", cub3d);
	}
	map->flood_map[y][x] = '1';
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
		ft_perror ("Error\nMalloc for cub3d->map.flood_map failed\n", cub3d);
	while (cub3d->map.game_map[++i])
		cub3d->map.flood_map[i] = ft_strdup(cub3d->map.game_map[i]);
	cub3d->map.flood_map[i] = NULL;
}
