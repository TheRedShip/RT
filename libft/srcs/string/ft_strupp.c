/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strupp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 15:24:06 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/04 15:31:29 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strupp(char *str)
{
	char	*cpy;
	char	*tmp;

	cpy = ft_strdup(str);
	tmp = cpy;
	while (*tmp)
	{
		if (ft_isupper(*tmp))
			*tmp -= 32;
		tmp++;
	}
	return (cpy);
}
