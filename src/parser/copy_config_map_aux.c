/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_config_map_aux.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:35:21 by jmarinho          #+#    #+#             */
/*   Updated: 2024/08/01 18:43:03 by jmarinho         ###   ########.fr       */
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

int	ft_check_empty_colors(char *line)
{
	if (ft_check_if_line_is_blank(line + 1))
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}

int	ft_check_for_configs_aux(t_game *cub3d, char *line)
{
    char *trimmed_line;

	if (line[0] == 'W' && line[1] == 'E' && cub3d->map.we_flag == false)
	{
		trimmed_line = ft_strtrim(line + 2, " 	\n");
		cub3d->map.config_map[WE] = ft_strdup(trimmed_line);
		free(trimmed_line);
		cub3d->map.we_flag = true;
		return (EXIT_SUCCESS);
	}
	else if (line[0] == 'F' && cub3d->map.f_flag == false)
	{
		if (ft_check_empty_colors(line))
			return (EXIT_FAILURE);
		trimmed_line = ft_strtrim(line + 1, " 	\n");
		cub3d->map.config_map[F] = ft_strdup(trimmed_line);
		free(trimmed_line);
		cub3d->map.f_flag = true;
		return (EXIT_SUCCESS);
	}
	else if (line[0] == 'C' && cub3d->map.c_flag == false)
	{
		if (ft_check_empty_colors(line))
			return (EXIT_FAILURE);
		trimmed_line = ft_strtrim(line + 1, " 	\n");
		cub3d->map.config_map[C] = ft_strdup(trimmed_line);
		free(trimmed_line);
		cub3d->map.c_flag = true;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	ft_check_for_configs(t_game *cub3d, char *line)
{
	char *trimmed_line;

	if (!line || line[0] == '\0')
		return (EXIT_SUCCESS);
	if (line[0] == 'N' && line[1] == 'O' && cub3d->map.no_flag == false)
	{
		trimmed_line = ft_strtrim(line + 2, " 	\n");
		cub3d->map.config_map[NO] = ft_strdup(trimmed_line);
		free(trimmed_line);
		cub3d->map.no_flag = true;
		return (EXIT_SUCCESS);
	}
	else if (line[0] == 'S' && line[1] == 'O' && cub3d->map.so_flag == false)
	{
		trimmed_line = ft_strtrim(line + 2, " 	\n");
		cub3d->map.config_map[SO] = ft_strdup(trimmed_line);
		free(trimmed_line);
		cub3d->map.so_flag = true;
		return (EXIT_SUCCESS);
	}
	else if (line[0] == 'E' && line[1] == 'A' && cub3d->map.ea_flag == false)
	{
		trimmed_line = ft_strtrim(line + 2, " 	\n");
		cub3d->map.config_map[EA] = ft_strdup(trimmed_line);
		free(trimmed_line);
		cub3d->map.ea_flag = true;
		return (EXIT_SUCCESS);
	}
	return (ft_check_for_configs_aux(cub3d, line));
}
