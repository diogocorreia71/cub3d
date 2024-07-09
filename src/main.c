/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:30:42 by jmarinho          #+#    #+#             */
/*   Updated: 2024/06/25 16:58:48 by jmarinho         ###   ########.fr       */
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

int	*ft_conv_str_to_int(char *str)
{
	char	**split;
	int		*int_rgb;
	int		i;

	i = -1;
	split = ft_split(str, ',');
	int_rgb = ft_calloc(3, sizeof(int));
	while (++i < 3)
		int_rgb[i] = ft_atoi(split[i]);
	ft_free_dp((void **)split);
	return (int_rgb);
}

int	main(int argc, char *argv[])
{
	t_game	cub3d;

	ft_check_b4_init(argc, argv, &cub3d); //linhas alocadas a mais?
	cub3d.lib = mlx_init();
	if (cub3d.lib == NULL)
		ft_perror("ERROR\nmlx_init failure\n", NULL);
	#//TODO map2.cub e map3.cub nao funcionam (colors?)
	#//TODO map6.cub and map8.cub check for leaks (sprites error induced)	
	cub3d.sprite[0] = ft_get_sprite_info(&cub3d, cub3d.map.config_map[NO]);
	cub3d.sprite[1] = ft_get_sprite_info(&cub3d, cub3d.map.config_map[SO]);
	cub3d.sprite[2] = ft_get_sprite_info(&cub3d, cub3d.map.config_map[EA]);
	cub3d.sprite[3] = ft_get_sprite_info(&cub3d, cub3d.map.config_map[WE]);
	cub3d.c_color = ft_shift_color(ft_conv_str_to_int(cub3d.map.config_map[C]));
	cub3d.f_color = ft_shift_color(ft_conv_str_to_int(cub3d.map.config_map[F]));
	cub3d.window = mlx_new_window(cub3d.lib, WIDTH, HEIGHT, "cub3D");
	if (cub3d.window == NULL)
		ft_perror("ERROR\nMalloc for cub3d.window failed\n", &cub3d);
	mlx_hook(cub3d.window, DestroyNotify, ButtonPressMask, ft_end_game, &cub3d);
	mlx_hook(cub3d.window, KeyPress, KeyPressMask, ft_keypress, &cub3d);
	mlx_hook(cub3d.window, KeyRelease, KeyReleaseMask, ft_keyrelease,
		&cub3d);
	ft_init_player_pos(&cub3d);
	mlx_loop_hook(cub3d.lib, ft_make_game, &cub3d); //leak fix distance to wall. Evitar divisão por 0 da perp_wall_dist
	mlx_loop(cub3d.lib);
}
