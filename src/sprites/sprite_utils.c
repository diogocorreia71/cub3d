/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:20:30 by jmarinho          #+#    #+#             */
/*   Updated: 2024/06/25 14:43:44 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_texture_calculus(t_game *cub3d)
{
	double	wall_x;

	cub3d->texture.index = NO;
	wall_x = 0;
	cub3d->img_info.tex_x = 0;
	if (cub3d->ray.hit_vertical == true)
		wall_x = cub3d->player.pos.y + cub3d->ray.perp_wall_dist * cub3d->ray.direction.y;
	else
		wall_x = cub3d->player.pos.x + cub3d->ray.perp_wall_dist * cub3d->ray.direction.x;
	wall_x -= floor(wall_x);
	cub3d->img_info.tex_x = (int)(wall_x * (int)SPRITE_SIZE);
	if ((cub3d->ray.hit_vertical == true && cub3d->ray.direction.x < 0)
		|| (cub3d->ray.hit_vertical == false && cub3d->ray.direction.y > 0))
		cub3d->img_info.tex_x = SPRITE_SIZE - cub3d->img_info.tex_x - 1;
	if (cub3d->ray.hit_vertical == false)
	{
		if (cub3d->ray.direction.y < 0)
			cub3d->texture.index = NO;
		else
			cub3d->texture.index = SO;
	}
	else if (cub3d->ray.hit_vertical == true)
	{
		if (cub3d->ray.direction.x < 0)
			cub3d->texture.index = WE;
		else
			cub3d->texture.index = EA;
	}
}

void	ft_get_img_address(t_image *img)
{
	img->address = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel,
			&img->line_length, &img->endian);
}

t_sprite    ft_get_sprite_info(t_game *cub3d, char *texture)
{
    t_sprite    sprite;

    sprite.image.img_ptr = mlx_xpm_file_to_image(cub3d->lib, texture,
			&sprite.width, &sprite.height);
    if (!sprite.image.img_ptr)
        ft_perror("ERROR\nMalloc of sprite.image.img_ptr\n", cub3d);
    ft_get_img_address(&sprite.image);
    if (!sprite.image.address)
        ft_perror("ERROR\nMalloc of sprite.image.address\n", cub3d);
    return (sprite);
}