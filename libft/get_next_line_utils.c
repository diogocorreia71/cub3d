/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:31:25 by jmarinho          #+#    #+#             */
/*   Updated: 2024/06/25 18:15:22 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen2(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr2(char *temp, char line_break)
{
	int	i;

	i = 0;
	if (!temp)
		return (NULL);
	while (temp[i])
	{
		if (temp[i] == line_break)
			return (&temp[i]);
		i++;
	}
	return (NULL);
}

char	*ft_strjoin2(char *temp, char *buffer)
{
	int		i;
	int		j;
	char	*strjoin;

	i = -1;
	j = 0;
	if (!temp)
	{
		temp = malloc(sizeof(char) * 1);
		temp[0] = '\0';
	}
	strjoin = malloc(sizeof(char) *((ft_strlen2(temp)
					+ ft_strlen2(buffer)) + 1));
	if (!strjoin)
		return (NULL);
	while (temp[++i])
		strjoin[i] = temp[i];
	while (buffer[j])
		strjoin[i++] = buffer[j++];
	strjoin[i] = '\0';
	free(temp);
	return (strjoin);
}

char	*ft_get_line(char *temp)
{
	int		i;
	char	*line;

	i = 0;
	if (!temp[i])
		return (NULL);
	while (temp[i] != '\0' && temp[i] != '\n')
		i++;
	if (temp[i] == '\0')
		line = malloc(sizeof(char) * (i + 1));
	else
		line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (temp[i] != '\0' && temp[i] != '\n')
	{
		line[i] = temp[i];
		i++;
	}
	if (temp[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_new_temp(char *temp)
{
	int		i;
	int		j;
	char	*new_temp;

	i = 0;
	j = 0;
	while (temp[i] != '\0' && temp[i] != '\n')
		i++;
	if (temp[i] == '\0')
	{
		free(temp);
		return (NULL);
	}
	new_temp = malloc(sizeof(char) * (ft_strlen2(temp) - i + 1));
	if (!new_temp)
		return (NULL);
	i = i + 1;
	while (temp[i])
		new_temp[j++] = temp[i++];
	new_temp[j] = '\0';
	free(temp);
	return (new_temp);
}
