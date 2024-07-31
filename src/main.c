/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diodos-s <diodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:30:42 by jmarinho          #+#    #+#             */
/*   Updated: 2024/07/31 12:41:48 by diodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_shift_color(int *rgb)
{
	int	color;

	color = (rgb[0] << 16 | rgb[1] << 8
			| rgb[2]);
	free (rgb);
	return (color);
}

void	ft_color_error(t_game *cub3d, int *int_rgb, char **split)
{
	ft_free_dp((void **)split);
	free (int_rgb);
	ft_perror("Error\nInvalid color configuration\n", cub3d);
}

int	*ft_conv_str_to_int(char *str, t_game *cub3d)
{
	char	**split;
	int		*int_rgb;
	int		i;

	i = -1;
	split = ft_split(str, ',');
	int_rgb = ft_calloc(3, sizeof(int));
	while (++i < 3)
	{
		if (!split[i])
			ft_color_error(cub3d, int_rgb, split);
		int_rgb[i] = ft_atoi(split[i]);
		if (int_rgb[i] < 0 || int_rgb[i] > 255)
			ft_color_error(cub3d, int_rgb, split);
	}
	i = -1;
	while (split[++i])
	if (i > 2)
		ft_color_error(cub3d, int_rgb, split);	
	ft_free_dp((void **)split);
	return (int_rgb);
}

void	ft_init_sprites(t_game *cub3d)
{
	cub3d->sprite[0] = ft_get_sprite_info(cub3d, cub3d->map.config_map[NO]);
	cub3d->sprite[1] = ft_get_sprite_info(cub3d, cub3d->map.config_map[SO]);
	cub3d->sprite[2] = ft_get_sprite_info(cub3d, cub3d->map.config_map[EA]);
	cub3d->sprite[3] = ft_get_sprite_info(cub3d, cub3d->map.config_map[WE]);
}

int	main(int argc, char *argv[])
{
	t_game	cub3d;

	if (argc != 2)
		ft_perror("Error\nInvalid nbr of args\n", NULL);
	cub3d.lib = mlx_init();
	if (cub3d.lib == NULL)
		ft_perror("Error\nmlx_init failure\n", NULL);
	ft_memset(cub3d.sprite, 0, sizeof(t_sprite) * 4);
	ft_check_b4_init(argv, &cub3d);
	ft_init_sprites(&cub3d);
	cub3d.c_color = ft_shift_color(ft_conv_str_to_int(cub3d.map.config_map[C],
				&cub3d));
	cub3d.f_color = ft_shift_color(ft_conv_str_to_int(cub3d.map.config_map[F],
				&cub3d));
	cub3d.window = mlx_new_window(cub3d.lib, WIDTH, HEIGHT, "cub3D");
	if (cub3d.window == NULL)
		ft_perror("Error\nMalloc for cub3d.window failed\n", &cub3d);
	mlx_hook(cub3d.window, DestroyNotify, ButtonPressMask, ft_end_game, &cub3d);
	mlx_hook(cub3d.window, KeyPress, KeyPressMask, ft_keypress, &cub3d);
	mlx_hook(cub3d.window, KeyRelease, KeyReleaseMask, ft_keyrelease,
		&cub3d);
	ft_init_player_pos(&cub3d);
	mlx_loop_hook(cub3d.lib, ft_make_game, &cub3d);
	mlx_loop(cub3d.lib);
}
