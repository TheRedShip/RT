/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 03:35:56 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/28 20:50:40 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_manage_strings(char *s1, char *s2, char *c, int buffered)
{
	if (buffered & 0b001)
		free(s1);
	if (buffered & 0b010)
		free(s2);
	if (buffered & 0b100)
		free(c);
}

char	*ft_strjoin(char *s1, char *s2, char *c, int tofree)
{
	char	*ns;
	int		buffered;
	size_t	len1;
	size_t	len2;

	buffered = (!s1 + (2 * !s2)) | tofree;
	if (!s1)
		s1 = ft_strdup("");
	if (!s2)
		s2 = ft_strdup("");
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	ns = malloc((len1 + len2 + 1 + ft_strlen(c)) * sizeof(char));
	if (ns == NULL)
		return (ns);
	*ns = 0;
	ft_strcat(ns, s1);
	if (c)
		ft_strcat(ns, c);
	ft_strcat(ns, s2);
	ft_manage_strings(s1, s2, c, buffered);
	return (ns);
}
