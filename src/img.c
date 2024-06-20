/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d->img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:12:41 by jmarinho          #+#    #+#             */
/*   Updated: 2024/06/20 15:17:16 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* int	pixel_get(t_image *img, int pixel_x, int pixel_y)
{
	int	color;

	color = *(unsigned int *)(img->addr + (pixel_y * img->line_length
				+ pixel_x * (img->bits_per_pixel / 8)));
	return (color);
}*/

void	pixel_put(t_image *img, int pixelX, int pixelY, int color)
{
	char	*dst;

	dst = img->address + (pixelY * img->line_length
			+ pixelX * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	start_image_buffer(t_game *cub3d)
{
	cub3d->buffer.img_ptr = mlx_new_image(cub3d->lib, WIDTH, HEIGHT);
	cub3d->buffer.address = mlx_get_data_addr(cub3d->buffer.img_ptr, &cub3d->buffer.bits_per_pixel,
			&cub3d->buffer.line_length, &cub3d->buffer.endian);
}