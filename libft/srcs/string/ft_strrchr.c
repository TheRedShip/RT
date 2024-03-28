/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:16:47 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/28 00:22:34 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *s, int c)
{
	size_t	i;
	char	*str;

	str = s;
	i = ft_strlen(str);
	while (i > 0 && *(str + i) != (unsigned char)c)
		i--;
	if (i == 0 && (unsigned char)c != *(char *)str && (unsigned char)c != 0)
		return (NULL);
	return ((char *)str + i);
}
