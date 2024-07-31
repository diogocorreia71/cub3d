/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:35:40 by jmarinho          #+#    #+#             */
/*   Updated: 2024/07/31 11:30:28 by jmarinho         ###   ########.fr       */
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

void	ft_free_line_and_read(int *fd, char *line)
{
	free (line);
	line = get_next_line(*fd);
}
