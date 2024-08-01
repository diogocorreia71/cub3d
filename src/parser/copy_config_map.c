/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_config_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:48:23 by jmarinho          #+#    #+#             */
/*   Updated: 2024/08/01 19:00:11 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_copy_config_map(t_game *cub3d)
{
	char	*line;
	char	*clean_line;
	int		fd;
	int		i;

	i = -1;
	fd = open(cub3d->file, O_RDONLY);
	if (fd < 0)
		ft_perror("Error\nCouldn't open requested file\n", cub3d);
	line = get_next_line(fd);
	cub3d->map.lines_to_map++;
	while (line)
	{
		if (!ft_check_all_config_flags(cub3d))
		{
			while (ft_check_if_line_is_blank(line))
			{
				free (line);
				line = get_next_line(fd);
				cub3d->map.lines_to_map++;
			}
			break ;
		}
		clean_line = ft_strtrim(line, " 	\n");
		free (line);
		if (!clean_line || *clean_line == '\0')
		{
			free (clean_line);
			line = get_next_line(fd);
			cub3d->map.lines_to_map++;
			continue ;
		}
		if (ft_check_for_configs(cub3d, clean_line))
		{
			free (clean_line);
			line = get_next_line(fd);
			while (line)
			{
				free (line);
				line = get_next_line(fd);
			}
			ft_perror("Error\nInvalid config", cub3d);
		}
		free (clean_line);
		line = get_next_line(fd);
		cub3d->map.lines_to_map++;
	}
	while (line)
	{
		free (line);
		line = get_next_line(fd);
	}
	close(fd);
	cub3d->map.lines_to_map--;
	ft_check_rgb(cub3d);
 }
