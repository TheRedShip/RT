/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 15:23:05 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/04 15:24:13 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strlow(char *str)
{
	char	*cpy;
	char	*tmp;

	cpy = ft_strdup(str);
	tmp = cpy;
	while (*tmp)
	{
		if (ft_isupper(*tmp))
			*tmp += 32;
		tmp++;
	}
	return (cpy);
}
