/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 12:26:36 by jmarinho          #+#    #+#             */
/*   Updated: 2024/06/25 18:08:57 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_ray_intersections(t_game *cub3d)
{
	if (cub3d->ray.direction.x < 0)
	{
		cub3d->ray.map_mov.x = -1;
		cub3d->ray.intersection.x = (cub3d->player.pos.x
				- cub3d->player.int_pos_x) * cub3d->ray.delta.x;
	}
	else
	{
		cub3d->ray.map_mov.x = 1;
		cub3d->ray.intersection.x = (cub3d->player.int_pos_x + 1
				- cub3d->player.pos.x) * cub3d->ray.delta.x;
	}
	if (cub3d->ray.direction.y < 0)
	{
		cub3d->ray.map_mov.y = -1;
		cub3d->ray.intersection.y = (cub3d->player.pos.y
				- cub3d->player.int_pos_y) * cub3d->ray.delta.y;
	}
	else
	{
		cub3d->ray.map_mov.y = 1;
		cub3d->ray.intersection.y = (cub3d->player.int_pos_y + 1
				- cub3d->player.pos.y) * cub3d->ray.delta.y;
	}
}

void	ft_cast_a_ray(t_game *cub3d, int i)
{
	double	plane_var;

	plane_var = 2 * i / (double)WIDTH - 1;
	cub3d->ray.direction.x = cub3d->player.direction.x
		+ cub3d->player.plane.pos.x * plane_var;
	cub3d->ray.direction.y = cub3d->player.direction.y
		+ cub3d->player.plane.pos.y * plane_var;
	cub3d->ray.delta.x = fabs(1 / cub3d->ray.direction.x);
	cub3d->ray.delta.y = fabs(1 / cub3d->ray.direction.y);
	cub3d->player.int_pos_x = (int)cub3d->player.pos.x;
	cub3d->player.int_pos_y = (int)cub3d->player.pos.y;
	ft_ray_intersections(cub3d);
}

void	ft_dda(t_game *cub3d)
{
	int	hit_flag;

	hit_flag = false;
	while (!hit_flag)
	{
		if (cub3d->ray.intersection.x < cub3d->ray.intersection.y)
		{
			cub3d->ray.intersection.x += cub3d->ray.delta.x;
			cub3d->player.int_pos_x += cub3d->ray.map_mov.x;
			cub3d->ray.hit_vertical = true;
		}
		else
		{
			cub3d->ray.intersection.y += cub3d->ray.delta.y;
			cub3d->player.int_pos_y += cub3d->ray.map_mov.y;
			cub3d->ray.hit_vertical = false;
		}
		if (cub3d->map.game_map[cub3d->player.int_pos_y]
			[cub3d->player.int_pos_x] == '1')
			hit_flag = true;
	}
}

void	ft_distance_to_the_wall(t_game *cub3d)
{
	if (cub3d->ray.hit_vertical == true)
		cub3d->ray.perp_wall_dist = (cub3d->ray.intersection.x
				- cub3d->ray.delta.x);
	else
		cub3d->ray.perp_wall_dist = (cub3d->ray.intersection.y
				- cub3d->ray.delta.y);
	cub3d->img_info.line_height = fabs((HEIGHT / cub3d->ray.perp_wall_dist));
	cub3d->img_info.draw_start = HEIGHT / 2 - cub3d->img_info.line_height / 2 ;
	if (cub3d->img_info.draw_start < 0)
		cub3d->img_info.draw_start = 0;
	cub3d->img_info.draw_end = HEIGHT / 2 + cub3d->img_info.line_height / 2;
	if (cub3d->img_info.draw_end >= HEIGHT)
		cub3d->img_info.draw_end = HEIGHT;
	cub3d->img_info.scale = SPRITE_SIZE / cub3d->img_info.line_height;
	cub3d->img_info.pos_texture = (cub3d->img_info.draw_start - (int)HEIGHT / 2
			+ cub3d->img_info.line_height / 2) * cub3d->img_info.scale;
}

void	ft_raycast_by_lodev(t_game *cub3d)
{
	int	i;

	i = -1;
	cub3d->ray.hit_vertical = false;
	while (++i <= (int)WIDTH)
	{
		ft_cast_a_ray(cub3d, i);
		ft_dda(cub3d);
		ft_distance_to_the_wall(cub3d);
		ft_texture_calculus(cub3d);
		ft_color(cub3d, i, 'c');
		ft_sprites(cub3d, i);
		ft_color(cub3d, i, 'f');
	}
	mlx_put_image_to_window(cub3d->lib, cub3d->window,
		cub3d->image.img_ptr, 0, 0);
	mlx_destroy_image(cub3d->lib, cub3d->image.img_ptr);
}
