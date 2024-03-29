/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 13:02:45 by rgramati          #+#    #+#             */
/*   Updated: 2024/03/28 20:50:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcspn(char *s, char *rejects)
{
	char	*tmp;

	tmp = s;
	while (*tmp)
	{
		if (ft_strchr(rejects, *tmp))
			return (tmp - s);
		tmp++;
	}
	return (tmp - s);
}

char	*ft_strtok(char *str, char *token)
{
	static char		*save;

	if (str)
		save = str;
	if (!save || !token)
		return (NULL);
	str = save;
	if (!*str)
		return (NULL);
	save += ft_strcspn(str, token);
	if (*save)
		*save++ = 0;
	return (str);
}
