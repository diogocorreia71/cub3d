/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:49:55 by jmarinho          #+#    #+#             */
/*   Updated: 2023/04/14 14:58:37 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	main(void)
{
	char	src[] = "++++++++++";
	unsigned char	*str;
//	size_t		i;
	size_t		k;

	k = 5;
	printf("ft_isalpha:%i\n", ft_isalpha('a'));
	printf("ft_isdigit:%i\n", ft_isdigit('1'));
	printf("ft_isalnum:%i\n", ft_isalnum('1'));
	printf("ft_isascii:%i\n", ft_isascii('1'));
	printf("ft_isprint:%i\n", ft_isprint('1'));
	printf("ft_strlen:%zu\n", ft_strlen("ricardo"));
	str = ft_memset(src, 'a', k);
	printf("ft_memset:%s\n", str);
	str = memset(src, 'a', k);
	printf("memset:%s\n", str);
	ft_bzero(src, k);
	printf("ft_bzero:%s\n", str);
	bzero(src, k);
        printf("bzero:%s\n", str);
	char    src1[] = "tttttttt";
	char    dest1[] = "++++++++++";
	str = ft_memcpy(dest1, src1, k);
	printf("ft_memcpy:%s\n", str);
	str = memcpy(dest1, src1, k);
	printf("memcpy:%s\n", str);

	str = ft_memmove(dest1, src1, k);
	printf("ft_memmove:%s\n", str);
	str = memmove(dest1, src1, k);
        printf("memmove:%s\n", str);

//	i = ft_strlcpy(dest1, src1, k);
//	printf("ft_strlcpy:%zu\n", i);

//no fim colocar ft_atoi
}
