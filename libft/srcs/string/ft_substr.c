/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 02:19:50 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/27 23:36:18 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	i = 0;
	while (*(char *)(s + start + i) != 0 && i < len)
		i ++;
	str = malloc((i + 1) * sizeof(char));
	if (str == NULL)
		return (str);
	ft_strlcpy(str, (char *)(s + start), i + 1);
	return (str);
}
