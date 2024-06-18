/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 20:34:30 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/17 12:38:06 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	print_map(char **map)
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

void	ft_check_rgb(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 3;
	while (++i < 6)
	{
		j = -1;
		while (mlx->map.config_map[i][++j])
		{
			if (mlx->map.config_map[i][j] == ',')
				continue ;
			else if (!ft_isdigit(mlx->map.config_map[i][j]) && ft_atoi(&mlx->map.config_map[i][j]) <= 255
				&& ft_atoi(&mlx->map.config_map[i][j]) >= 0)
				ft_perror("ERROR\nRGB values must be 3 and integers\n", mlx);
		}
	}
}
