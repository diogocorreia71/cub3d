/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:35:40 by jmarinho          #+#    #+#             */
/*   Updated: 2024/08/02 15:09:00 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_free_stack_array(void **arg)
{
	int	i;

	i = -1;
	if (!arg)
		return ;
	while (++i < 6)
	{
		if (arg[i])
			free(arg[i]);
	}
}

void	ft_free_dp(void **arg)
{
	int	i;

	i = 0;
	if (!arg)
		return ;
	while (arg[i] != NULL && arg[i] != 0)
	{
		if (arg[i])
			free(arg[i]);
		i++;
	}
	free(arg);
}

void	ft_check_commas(char *str, t_game *cub3d)
{
	int	comma_count;
	int	i;

	comma_count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			comma_count++;
		i++;
	}
	if (comma_count != 2)
		ft_color_error(cub3d, NULL, NULL);
}

int	*ft_convert_and_validate(char **trimmed_line, t_game *cub3d)
{
	int	*int_rgb;
	int	i;
	int	j;

	int_rgb = ft_calloc(3, sizeof(int));
	if (!int_rgb)
		ft_perror("Error\nMemory allocation failed\n", cub3d);
	i = 0;
	j = -1;
	while (i < 3)
	{
		if (!trimmed_line[i] || trimmed_line[i][0] == '\0')
			ft_color_error(cub3d, int_rgb, trimmed_line);
		j = -1;
		while (trimmed_line[i][++j])
		{
			if (!ft_isdigit(trimmed_line[i][j]))
				ft_color_error(cub3d, int_rgb, trimmed_line);
		}
		int_rgb[i] = ft_atoi(trimmed_line[i]);
		if (int_rgb[i] < 0 || int_rgb[i] > 255)
			ft_color_error(cub3d, int_rgb, trimmed_line);
		i++;
	}
	return (int_rgb);
}
