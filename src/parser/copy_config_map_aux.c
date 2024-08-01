/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_config_map_aux.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:35:21 by jmarinho          #+#    #+#             */
/*   Updated: 2024/08/01 19:22:14 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_check_empty_colors(char *line)
{
	if (ft_check_if_line_is_blank(line + 1))
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}

int	handle_texture_config(t_game *cub3d, char *line, int index, bool *flag)
{
	char	*trimmed_line;

	trimmed_line = ft_strtrim(line + 2, " \t\n");
	cub3d->map.config_map[index] = ft_strdup(trimmed_line);
	free(trimmed_line);
	*flag = true;
	return (EXIT_SUCCESS);
}

int	handle_color_config(t_game *cub3d, char *line, int index, bool *flag)
{
	char	*trimmed_line;

	if (ft_check_empty_colors(line))
	{
		return (EXIT_FAILURE);
	}
	trimmed_line = ft_strtrim(line + 1, " \t\n");
	cub3d->map.config_map[index] = ft_strdup(trimmed_line);
	free(trimmed_line);
	*flag = true;
	return (EXIT_SUCCESS);
}

int	ft_check_for_configs_aux(t_game *cub3d, char *line)
{
	if (line[0] == 'W' && line[1] == 'E' && cub3d->map.we_flag == false)
		return (handle_texture_config(cub3d, line, WE, &cub3d->map.we_flag));
	else if (line[0] == 'F' && cub3d->map.f_flag == false)
		return (handle_color_config(cub3d, line, F, &cub3d->map.f_flag));
	else if (line[0] == 'C' && cub3d->map.c_flag == false)
		return (handle_color_config(cub3d, line, C, &cub3d->map.c_flag));
	return (EXIT_FAILURE);
}

int	ft_check_for_configs(t_game *cub3d, char *line)
{
	if (!line || line[0] == '\0')
		return (EXIT_SUCCESS);
	if (line[0] == 'N' && line[1] == 'O' && cub3d->map.no_flag == false)
		return (handle_texture_config(cub3d, line, NO, &cub3d->map.no_flag));
	else if (line[0] == 'S' && line[1] == 'O' && cub3d->map.so_flag == false)
		return (handle_texture_config(cub3d, line, SO, &cub3d->map.so_flag));
	else if (line[0] == 'E' && line[1] == 'A' && cub3d->map.ea_flag == false)
		return (handle_texture_config(cub3d, line, EA, &cub3d->map.ea_flag));
	return (ft_check_for_configs_aux(cub3d, line));
}
