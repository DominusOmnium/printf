/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 16:23:21 by dkathlee          #+#    #+#             */
/*   Updated: 2020/01/14 10:19:44 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *src, size_t old_size, size_t new_size)
{
	unsigned char	*res;
	size_t			i;

	//write(1, "1_1\n", 4);
	if ((res = (unsigned char*)ft_memalloc(new_size)) == NULL)
		return (NULL);
	//write(1, "1_2\n", 4);
	if (old_size == 0 || src == NULL)
		return ((void*)res);
	//write(1, "1_3\n", 4);
	i = 0;
	while (i < old_size && i < new_size)
	{
		res[i] = ((unsigned char*)src)[i];
		i++;
	}
	free(src);
	return ((void*)res);
}
