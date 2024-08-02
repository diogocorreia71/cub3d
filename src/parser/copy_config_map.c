/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_config_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:48:23 by jmarinho          #+#    #+#             */
/*   Updated: 2024/08/02 14:37:46 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	open_config_file(t_game *cub3d)
{
	int	fd;

	fd = open(cub3d->file, O_RDONLY);
	if (fd < 0)
	{
		ft_perror("Error\nCouldn't open requested file\n", cub3d);
	}
	return (fd);
}

void	process_config_line(t_game *cub3d, int fd, char *line)
{
	char	*clean_line;

	clean_line = ft_strtrim(line, " \t\n");
	free(line);
	if (!clean_line || *clean_line == '\0')
	{
		free(clean_line);
		return ;
	}
	if (ft_check_for_configs(cub3d, clean_line))
	{
		while (clean_line)
		{
			free(clean_line);
			clean_line = get_next_line(fd);
		}
		ft_perror("Error\nInvalid config\n", cub3d);
	}
	free(clean_line);
}

void	skip_blank_lines(char **line, int fd, int *lines_to_map)
{
	while (ft_check_if_line_is_blank(*line))
	{
		free(*line);
		*line = get_next_line(fd);
		(*lines_to_map)++;
	}
}

void	copy_config_map_lines(t_game *cub3d, int fd)
{
	char	*line;

	line = get_next_line(fd);
	cub3d->map.lines_to_map++;
	while (line)
	{
		if (!ft_check_all_config_flags(cub3d))
		{
			skip_blank_lines(&line, fd, &cub3d->map.lines_to_map);
			break ;
		}
		process_config_line(cub3d, fd, line);
		line = get_next_line(fd);
		cub3d->map.lines_to_map++;
	}
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}

void	ft_copy_config_map(t_game *cub3d)
{
	int	fd;

	fd = open_config_file(cub3d);
	if (fd < 0)
		return ;
	copy_config_map_lines(cub3d, fd);
	close(fd);
	cub3d->map.lines_to_map--;
}
