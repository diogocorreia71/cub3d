/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:35:40 by jmarinho          #+#    #+#             */
/*   Updated: 2024/07/30 17:39:11 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		printf("%s", map[i++]);
}

void	ft_free_stack_array(void **arg)
{
	int	i;

	i = -1;
	while (++i < 6)
	{
		if (arg[i])
			free(arg[i]);
	}
}

void	ft_check_rgb(t_game *cub3d)
{
	int	i;
	int	j;

	i = 3;
	while (++i < 6)
	{
		j = -1;
		while (cub3d->map.config_map[i][++j])
		{
			if (cub3d->map.config_map[i][j] == ',')
				continue ;
			else if (!ft_isdigit(cub3d->map.config_map[i][j])
				&& ft_atoi(&cub3d->map.config_map[i][j]) <= 255
				&& ft_atoi(&cub3d->map.config_map[i][j]) >= 0)
				ft_perror("Error\nRGB values must be 3 and integers\n", cub3d);
		}
	}
}

void	ft_free_dp(void **arg)
{
	int	i;

	i = 0;
	if (!arg)
		return ;
	while (arg[i] != NULL && arg[i] != 0)
	{
		if (arg[i])
			free(arg[i]);	
		i++;
	}
	free(arg);
}

void	ft_read_next_line(t_game *cub3d, int *fd, char *line)
{

	int		i;

	i = -1;
	while (ft_check_if_line_is_blank(line))
	{
		free (line);
		line = get_next_line(*fd);
	}
/* 		if (!line)
		{
			close (*fd);
			ft_perror("Error\nWrong Config42\n", cub3d);
		} */
	while (line[++i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W' && line[i] != ' ' && line[i] != '\t'
			&& line[i] != '\n')
			{
				free(line);	
				ft_perror("Error\nWrong Map\n", cub3d);
			}
	}
		cub3d->map.lines_to_map++;
}
