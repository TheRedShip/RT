/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:24:44 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/27 14:24:52 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_incharset(char c, char *set)
{
	int	i;

	i = 0;
	while (*(set + i))
	{
		if (*(set + i) == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char *set)
{
	size_t		i;
	size_t		s;
	size_t		e;
	char		*trim;

	i = 0;
	s = 0;
	e = 0;
	if (!s1)
		return (NULL);
	while (i < ft_strlen(s1) && ft_incharset(*(char *)(s1 + i++), (char *)set))
		s++;
	i = ft_strlen(s1) - 1;
	if (s < ft_strlen(s1))
		while (i > 0 && ft_incharset(*(char *)(s1 + i--), (char *)set))
			e++;
	trim = malloc((ft_strlen(s1) - s - e + 1) * sizeof(char));
	if (!trim)
		return (NULL);
	ft_strlcpy(trim, s1 + s, (ft_strlen(s1) - s - e + 1));
	return (trim);
}
