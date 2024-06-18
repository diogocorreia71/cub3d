/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_b4_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:40:18 by jmarinho          #+#    #+#             */
/*   Updated: 2024/06/17 12:21:45 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_count_map_lines(t_mlx *mlx)
{
	int		fd;
	char	*line;

	mlx->map.total_lines = 0;
	fd = open(mlx->file, O_RDONLY);
	if (fd < 0)
		ft_perror("Error\nCouldn't open requested file\n", mlx);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		mlx->map.total_lines++;
		free(line);
	}
	close(fd);
}

int	ft_check_filename(t_mlx *mlx)
{
	char	*str;

	str = mlx->file;
	if (ft_strnstr(str + ft_strlen(str) - 4, ".cub", 4))
		return (EXIT_SUCCESS);
	else
		ft_perror("Error\nInvalid. Try maps/<map_name>.cub\n", mlx);
	return (0);
}

void	ft_check_b4_init(int ac, char **av, t_mlx *mlx)
{
	if (ac != 2)
		ft_perror("Error\nNumber of args are invalid!\n", mlx);
	mlx->file = av[1];
	ft_memset(&mlx->map, 0, sizeof(t_map));
	ft_count_map_lines(mlx);
	ft_check_filename(mlx);
	ft_copy_config_map(mlx);
	ft_copy_game_map(mlx);
	ft_check_game_map(mlx);
}

void	ft_perror(char *msg, t_mlx *mlx)
{
	ft_fprintf(2, "%s", msg);
	if (mlx->lib)
	{
		mlx_destroy_display(mlx->lib);
		free (mlx->lib);
	}
	ft_free_stack_array((void **)mlx->map.config_map);
	if (mlx->map.game_map)
		ft_free_dp((void **)mlx->map.game_map);
	exit (EXIT_SUCCESS);
}
