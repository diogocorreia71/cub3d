/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:12:41 by jmarinho          #+#    #+#             */
/*   Updated: 2024/06/25 12:01:56 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	pixel_get(t_image *img, int pixel_x, int pixel_y)
{
	int	color;

	color = *(unsigned int *)(img->address + (pixel_y * img->line_length
		+ pixel_x * (img->bits_per_pixel / 8)));
	return (color);
}

void	pixel_put(t_image *img, int pixelX, int pixelY, int color)
{
	char	*dst;

	dst = img->address + (pixelY * img->line_length
			+ pixelX * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_sprites(t_game *cub3d, int i)
{
	int	texture;
	int	tex_y;

	while (cub3d->img_info.draw_start < cub3d->img_info.draw_end)
	{
		tex_y = (int)cub3d->img_info.pos_texture & (SPRITE_SIZE - 1);
		cub3d->img_info.pos_texture += cub3d->img_info.scale;
		texture = pixel_get(&cub3d->sprite[cub3d->texture.index].image,
				cub3d->img_info.tex_x, tex_y);
		pixel_put(&cub3d->image, i, cub3d->img_info.draw_start++, texture);//0xFF0000 para as paredes em vermelho para teste
	}
}

void	ft_color(t_game *cub3d, int i, char flag)
{
	int	y;

	y = -1;
	if (flag == 'c')
	{
		while (++y < cub3d->img_info.draw_start)
			pixel_put(&cub3d->image, i, y, cub3d->c_color);
	}
	else if (flag == 'f')
	{
		while (cub3d->img_info.draw_end < (int)HEIGHT)
			pixel_put(&cub3d->image, i, cub3d->img_info.draw_end++, cub3d->f_color);
	}
}

void	ft_image_buffer(t_game *cub3d)
{
	cub3d->image.img_ptr = mlx_new_image(cub3d->lib, WIDTH, HEIGHT);
	cub3d->image.address = mlx_get_data_addr(cub3d->image.img_ptr, &cub3d->image.bits_per_pixel,
			&cub3d->image.line_length, &cub3d->image.endian);
}
