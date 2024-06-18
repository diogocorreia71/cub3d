/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_config_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:48:23 by jmarinho          #+#    #+#             */
/*   Updated: 2024/06/17 14:37:26 by jmarinho         ###   ########.fr       */
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

int	ft_check_for_configs(t_game *cub3d, char *line)
{
	if (!line || line[0] == '\0')
		return 0;
	if (line[0] == 'N' && line[1] == 'O' && cub3d->map.no_flag == false)
	{
		cub3d->map.config_map[NO] = ft_strdup(line + 2);
		cub3d->map.no_flag = true;
	}
	else if (line[0] == 'S' && line[1] == 'O' && cub3d->map.so_flag == false)
	{
		cub3d->map.config_map[SO] = ft_strdup(line + 2);
		cub3d->map.so_flag = true;
	}
	else if (line[0] == 'E' && line[1] == 'A' && cub3d->map.ea_flag == false)
	{
		cub3d->map.config_map[EA] = ft_strdup(line + 2);
		cub3d->map.ea_flag = true;
	}
	else if (line[0] == 'W' && line[1] == 'E' && cub3d->map.we_flag == false)
	{
		cub3d->map.config_map[WE] = ft_strdup(line + 2);
		cub3d->map.we_flag = true;
	}
	else if (line[0] == 'F' && cub3d->map.f_flag == false)
	{
		cub3d->map.config_map[F] = ft_strdup(line + 1);
		cub3d->map.f_flag = true;
	}
	else if (line[0] == 'C' && cub3d->map.c_flag == false)
	{
		cub3d->map.config_map[C] = ft_strdup(line + 1);
		cub3d->map.c_flag = true;
	}
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	ft_copy_config_map(t_game *cub3d)
{
	char	*line;
	char	*clean_line;
	int		i;
	int		k;
	int		fd;

	fd = open(cub3d->file, O_RDONLY);
	if (fd < 0)
		ft_perror("Error\nCouldn't open requested file\n", cub3d);
	line = get_next_line(fd);
	cub3d->map.lines_to_map++;
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
		clean_line = malloc(sizeof(char) * ft_strlen(line));
		if (!clean_line)
		{
			free (line);
			close(fd);
			ft_perror ("ERROR\nMalloc for clean_line failed\n", cub3d);
		}
		clean_line[0] = '\0';
		while (line && line[++i])
		{
			if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
				clean_line[++k] = line[i];
		}
		if (k == -1)
			k = 0;
		clean_line[k + 1] = '\0';
		if (ft_check_for_configs(cub3d, clean_line))
		{
			while (line)
			{
				free (line);
				line = get_next_line(fd);
			}
			free (clean_line);
			close(fd);
			ft_perror("ERROR\nWrong configuration detected\n", cub3d);
		}
		if (line)
			free (line);
		free (clean_line);
		if (!ft_check_all_config_flags(cub3d))
			break ;
		line = get_next_line(fd);
		cub3d->map.lines_to_map++;
	}
	line = get_next_line(fd);
	while (ft_check_if_line_is_blank(line))
	{
		free (line);
		line = get_next_line(fd);
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
