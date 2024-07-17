/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_b4_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:40:18 by jmarinho          #+#    #+#             */
/*   Updated: 2024/07/17 14:49:27 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_count_map_lines(t_game *cub3d)
{
	int		fd;
	char	*line;

	cub3d->map.total_lines = 0;
	fd = open(cub3d->file, O_RDONLY);
	if (fd < 0)
		ft_perror("Error\nCouldn't open requested file\n", cub3d);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		cub3d->map.total_lines++;
		free(line);
	}
	close(fd);
}

int	ft_check_filename(t_game *cub3d)
{
	int	fd;

	fd = open(cub3d->file, O_RDONLY);
	if (fd < 0)
		ft_perror("Error\nCouldn't open requested file\n", cub3d);
	close (fd);
	if (ft_strnstr(cub3d->file + ft_strlen(cub3d->file) - 4, ".cub", 4))
		return (EXIT_SUCCESS);
	else
		ft_perror("Error\nInvalid. Try maps/<map_name>.cub\n", cub3d);
	return (0);
}

void	ft_check_b4_init(int ac, char **av, t_game *cub3d)
{
	if (ac != 2)
		ft_perror("Error\nNumber of args are invalid!\n", cub3d);
	cub3d->file = av[1];
	ft_memset(&cub3d->map, 0, sizeof(t_map));
	ft_check_filename(cub3d);
	ft_count_map_lines(cub3d);
	ft_copy_config_map(cub3d);
	ft_copy_game_map(cub3d);
	ft_check_game_map(cub3d);
}

void	ft_perror(char *msg, t_game *cub3d)
{
	printf("%s", msg);
	if (!cub3d)
		exit (EXIT_FAILURE);
	if (cub3d->lib)
	{
		mlx_destroy_display(cub3d->lib);
		free (cub3d->lib);
	}
	ft_free_stack_array((void **)cub3d->map.config_map);
	if (cub3d->map.game_map)
		ft_free_dp((void **)cub3d->map.game_map);	
	exit (EXIT_SUCCESS);
}
