/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 00:48:02 by rgramati          #+#    #+#             */
/*   Updated: 2024/03/04 23:43:12 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, char *src)
{
	char	*tmp;

	tmp = dest;
	if (!dest || !src)
		return (NULL);
	while (*dest)
		dest++;
	while (*src)
		*(dest++) = *(src++);
	*dest = 0;
	return (tmp);
}

size_t	ft_strlcat(char *dst, char *src, size_t size, int null_term)
{
	size_t	i;
	size_t	len;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	len = ft_strlen(dst);
	if (len > size)
		return (ft_strlen(src) + size);
	if (!*(src + i))
		return (len);
	while (*(src + i) && i + len + 1 < size)
	{
		*(dst + len + i) = *(src + i);
		i ++;
	}
	if (null_term)
		*(dst + len + i) = '\0';
	while (*(src + i))
		i++;
	return (len + i);
}
