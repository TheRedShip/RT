/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 18:42:06 by rgramati          #+#    #+#             */
/*   Updated: 2024/03/05 00:13:50 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *str, int n)
{
	char	*cpy;
	char	*tmp;

	cpy = malloc((ft_max(n, ft_strlen(str)) + 1) * sizeof(char));
	if (!cpy)
		return (NULL);
	tmp = cpy;
	while (*str && n--)
		*(cpy++) = *(str++);
	*cpy = 0;
	return (tmp);
}

char	*ft_strdup(char *str)
{
	char	*cpy;
	char	*tmp;

	cpy = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!cpy)
		return (NULL);
	tmp = cpy;
	while (*str)
		*(cpy++) = *(str++);
	*cpy = 0;
	return (tmp);
}
