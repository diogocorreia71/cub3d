/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_game_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:35:11 by jmarinho          #+#    #+#             */
/*   Updated: 2024/07/25 15:37:35 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_check_if_line_is_blank(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

char	*ft_copy_game_map_checker(t_game *cub3d, char *line, int fd)
{
	if (!ft_check_if_line_is_blank(line))
	{
		while (line)
		{
			free (line);
			line = get_next_line(fd);
		}
		close(fd);
		ft_perror("Error\nInvalid Map\n", cub3d);
	}
	return (line);
}

void	ft_copy_game_map_aux(t_game *cub3d, char *line, int fd)
{
	int		i;

	i = -1;
	while (line)
	{
		if (ft_check_if_line_is_blank(line))
		{
			free (line);
			break ;
		}
		cub3d->map.game_map[++i] = ft_strdup(line);
		free (line);
		line = get_next_line(fd);
	}
	line = get_next_line(fd);
	while (line)
	{
		line = ft_copy_game_map_checker(cub3d, line, fd);
		free (line);
		line = get_next_line(fd);
	}
	cub3d->map.game_map[i + 1] = NULL;
	close(fd);
}

void	ft_copy_game_map(t_game *cub3d)
{
	int		i;
	int		fd;
	char	*line;

	cub3d->map.game_map = ft_calloc(sizeof(char *), cub3d->map.total_lines);
	if (!cub3d->map.game_map)
		ft_perror ("Error\nCalloc for cub3d->map.game_map failed\n", cub3d);
	fd = open(cub3d->file, O_RDONLY);
	if (fd < 0)
		ft_perror("Error\nCouldn't open requested file\n", cub3d);
	line = get_next_line(fd);
	i = -1;
	while (++i < cub3d->map.lines_to_map)
	{
		free (line);
		line = get_next_line(fd);
	}
	ft_copy_game_map_aux(cub3d, line, fd);
	close(fd);
}
