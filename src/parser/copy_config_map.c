/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_config_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:48:23 by jmarinho          #+#    #+#             */
/*   Updated: 2024/07/30 17:59:00 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_check_if_complete(t_game *cub3d, char *line, int fd)
{
	if (ft_check_for_configs(cub3d, cub3d->map.clean_line))
	{
		while (line)
		{
			free (line);
			line = get_next_line(fd);
		}
		free (cub3d->map.clean_line);
		close(fd);
		ft_perror("Error\nWrong configuration detected\n", cub3d);
	}
}

void	ft_copy_config_map_cicle_aux(t_game *cub3d, char *line, int fd)
{
	cub3d->map.clean_line = malloc(sizeof(char) * ft_strlen(line));
	if (!cub3d->map.clean_line)
	{
		free (line);
		close(fd);
		ft_perror ("Error\nMalloc for cub3d->map.clean_line failed\n", cub3d);
	}
	cub3d->map.clean_line[0] = '\0';
}

void	ft_copy_config_map_cicle_aux2(t_game *cub3d, char *line, int i, int k)
{
	while (line && line[++i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			cub3d->map.clean_line[++k] = line[i];
	}
	if (k == -1)
		k = 0;
	cub3d->map.clean_line[k + 1] = '\0';
}

void	ft_copy_config_map_cicle(t_game *cub3d, char *line, int fd)
{
	int		i;
	int		k;

	while (line)
	{
		i = -1;
		k = -1;
		if (!line || line[0] == '\n')
		{
			free (line);
			line = get_next_line(fd);
			cub3d->map.lines_to_map++;
			continue ;
		}
		ft_copy_config_map_cicle_aux(cub3d, line, fd);
		ft_copy_config_map_cicle_aux2(cub3d, line, i, k);
		ft_check_if_complete(cub3d, line, fd);
		free (line);
		free (cub3d->map.clean_line);
		if (!ft_check_all_config_flags(cub3d))
			break ;
		line = get_next_line(fd);
		cub3d->map.lines_to_map++;
	}
}

void	ft_copy_config_map(t_game *cub3d)
{
	char	*line;
	int		fd;

	fd = open(cub3d->file, O_RDONLY);
	if (fd < 0)
		ft_perror("Error\nCouldn't open requested file\n", cub3d);
	line = get_next_line(fd);
	cub3d->map.lines_to_map++;
	ft_copy_config_map_cicle(cub3d, line, fd);
	line = get_next_line(fd);
	if (!line)
		ft_perror("Error\nInvalid config\n", cub3d);
	while (ft_check_if_line_is_blank(line))
	{
		free (line);
		line = get_next_line(fd);
		if (!line)
			ft_perror("Error\nInvalid config\n", cub3d);
		cub3d->map.lines_to_map++;
	}
	while (line)
	{
		free (line);
		line = get_next_line(fd);
	}
	close(fd);
	ft_check_rgb(cub3d);
}
