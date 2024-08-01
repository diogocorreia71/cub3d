/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:35:40 by jmarinho          #+#    #+#             */
/*   Updated: 2024/08/01 18:06:13 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		printf("%s", map[i++]);
}

void	ft_free_stack_array(void **arg)
{
	int	i;

	i = -1;
	if (!arg)
		return ;
	while (++i < 6	)
	{
		if (arg[i])
			free(arg[i]);
	}
}
 
void	ft_check_rgb(t_game *cub3d)
{
	int	i;
	int	j;

	i = 3;
	while (++i < 6)
	{
		j = -1;
		while (cub3d->map.config_map[i][++j])
		{
			if (cub3d->map.config_map[i][j] == ',')
				continue ;
			else if (!ft_isdigit(cub3d->map.config_map[i][j]))
				ft_perror("Error\nRGB values must be 3 and integers\n", cub3d);
		}
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

void    ft_check_commas(char *str, t_game *cub3d)
{
    int comma_count;
    int i;
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
int *ft_convert_and_validate(char **split, t_game *cub3d)
{
    int *int_rgb;
    int i;
    int_rgb = ft_calloc(3, sizeof(int));
    if (!int_rgb)
        ft_perror("Memory allocation failed", cub3d);
    i = 0;
    while (i < 3)
    {
        if (!split[i] || split[i][0] == '\0')
            ft_color_error(cub3d, int_rgb, split);
        int_rgb[i] = ft_atoi(split[i]);
        if (int_rgb[i] < 0 || int_rgb[i] > 255)
            ft_color_error(cub3d, int_rgb, split);
        i++;
    }
    return (int_rgb);
}