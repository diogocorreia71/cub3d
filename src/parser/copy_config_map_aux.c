/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_config_map_aux.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:35:21 by jmarinho          #+#    #+#             */
/*   Updated: 2024/06/25 18:45:39 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_check_all_config_flags(t_game *cub3d)
{
	if (cub3d->map.no_flag == true && cub3d->map.so_flag == true
		&& cub3d->map.ea_flag == true && cub3d->map.we_flag == true
		&& cub3d->map.f_flag == true && cub3d->map.c_flag == true)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	ft_check_for_configs_aux(t_game *cub3d, char *line)
{
	if (line[0] == 'W' && line[1] == 'E' && cub3d->map.we_flag == false)
	{
		cub3d->map.config_map[WE] = ft_strdup(line + 2);
		cub3d->map.we_flag = true;
		return (EXIT_SUCCESS);
	}
	else if (line[0] == 'F' && cub3d->map.f_flag == false)
	{
		cub3d->map.config_map[F] = ft_strdup(line + 1);
		cub3d->map.f_flag = true;
		return (EXIT_SUCCESS);
	}
	else if (line[0] == 'C' && cub3d->map.c_flag == false)
	{
		cub3d->map.config_map[C] = ft_strdup(line + 1);
		cub3d->map.c_flag = true;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	ft_check_for_configs(t_game *cub3d, char *line)
{
	if (!line || line[0] == '\0')
		return (EXIT_SUCCESS);
	if (line[0] == 'N' && line[1] == 'O' && cub3d->map.no_flag == false)
	{
		cub3d->map.config_map[NO] = ft_strdup(line + 2);
		cub3d->map.no_flag = true;
		return (EXIT_SUCCESS);
	}
	else if (line[0] == 'S' && line[1] == 'O' && cub3d->map.so_flag == false)
	{
		cub3d->map.config_map[SO] = ft_strdup(line + 2);
		cub3d->map.so_flag = true;
		return (EXIT_SUCCESS);
	}
	else if (line[0] == 'E' && line[1] == 'A' && cub3d->map.ea_flag == false)
	{
		cub3d->map.config_map[EA] = ft_strdup(line + 2);
		cub3d->map.ea_flag = true;
		return (EXIT_SUCCESS);
	}
	return (ft_check_for_configs_aux(cub3d, line));
}
