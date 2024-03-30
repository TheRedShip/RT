/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 02:17:18 by rgramati          #+#    #+#             */
/*   Updated: 2024/03/01 17:51:46 by ycontre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	if (!s1 || !s2)
		return (s1 != s2);
	while (*s1 && *s1 == *s2 && n--)
	{
		s1++;
		s2++;
	}
	if (!n)
		return (0);
	return (*s1 - *s2);
}

int	ft_strcmp(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (s1 != s2);
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
