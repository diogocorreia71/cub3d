/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:20:30 by jmarinho          #+#    #+#             */
/*   Updated: 2024/06/17 15:55:43 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_get_img_address(t_image *img)
{
	img->address = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel,
			&img->line_length, &img->endian);
}

t_sprite    ft_get_sprite_info(t_game *cub3d, char *texture)
{
    t_sprite    sprite;

    sprite.img.img_ptr = mlx_xpm_file_to_image(cub3d->lib, texture,
			&sprite.width, &sprite.height);
    if (!sprite.img.img_ptr)
        ft_perror("ERROR\nMalloc of sprite.img.img_ptr\n", cub3d);
    ft_get_img_address(&sprite.img);
    if (!sprite.img.address)
        ft_perror("ERROR\nMalloc of sprite.img.address\n", cub3d);
    return (sprite);
}