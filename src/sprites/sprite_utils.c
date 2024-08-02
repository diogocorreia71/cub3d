/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:20:30 by jmarinho          #+#    #+#             */
/*   Updated: 2024/08/02 15:28:18 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_wall_x(t_game *cub3d)
{
	double	wall_x;
	t_rays	*ray;

	ray = &cub3d->ray;
	wall_x = 0;
	cub3d->img_info.tex_x = 0;
	if (ray->hit_vertical == true)
		wall_x = cub3d->player.pos.y + ray->perp_wall_dist * ray->direction.y;
	else
		wall_x = cub3d->player.pos.x + ray->perp_wall_dist * ray->direction.x;
	wall_x -= floor(wall_x);
	cub3d->img_info.tex_x = (int)(wall_x * (int)SPRITE_SIZE);
}

void	ft_texture_calculus(t_game *cub3d)
{
	t_rays	*ray;

	ray = &cub3d->ray;
	cub3d->texture.index = NO;
	ft_wall_x(cub3d);
	if ((ray->hit_vertical == true && ray->direction.x < 0)
		|| (ray->hit_vertical == false && ray->direction.y > 0))
		cub3d->img_info.tex_x = SPRITE_SIZE - cub3d->img_info.tex_x - 1;
	if (ray->hit_vertical == false)
	{
		if (ray->direction.y > 0)
			cub3d->texture.index = NO;
		else
			cub3d->texture.index = SO;
	}
	else if (ray->hit_vertical == true)
	{
		if (ray->direction.x > 0)
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

void	ft_check_xpm(t_game	*cub3d)
{
	int		i;
	char	*config_line;

	i = 0;
	while (i < 4)
	{
		config_line = cub3d->map.config_map[i];
		if (config_line && ft_strlen(config_line) >= 4
			&& ft_strnstr(config_line + ft_strlen(config_line) - 4, ".xpm", 4))
			i++;
		else
			ft_perror("Error\nInvalid. Try <sprite_name>.xpm\n", cub3d);
	}
}

t_sprite	ft_get_sprite_info(t_game *cub3d, char *texture)
{
	t_sprite	sprite;

	ft_check_xpm(cub3d);
	sprite.image.img_ptr = mlx_xpm_file_to_image(cub3d->lib, texture,
			&sprite.width, &sprite.height);
	if (!sprite.image.img_ptr)
		ft_perror("Error\nMalloc of sprite.image.img_ptr\n", cub3d);
	ft_get_img_address(&sprite.image);
	if (!sprite.image.address)
		ft_perror("Error\nMalloc of sprite.image.address\n", cub3d);
	return (sprite);
}
