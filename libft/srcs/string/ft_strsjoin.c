/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 10:26:32 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/29 18:00:33 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_manage_strings(char **strs, char *sep, int tf)
{
	if (tf & 0b01)
		ft_free_tab((void **) strs);
	if (tf & 0b10)
		free(sep);
}

static char	*ft_manage_join(char **strs, char **sep, int *tofree)
{
	if (!*sep)
	{
		*tofree |= 0b10;
		*sep = ft_strdup("");
	}
	if (!strs)
	{
		if (*tofree & 0b10)
			free(*sep);
		return (NULL);
	}
	if (!*strs)
	{
		if (*tofree & 0b10)
			free(*sep);
		return (ft_strdup(""));
	}
	return (*sep);
}

char	*ft_strsjoin(char **strs, char *sep, int tofree)
{
	char	**tmp;
	char	*check;
	char	*ns;
	int		len;

	check = ft_manage_join(strs, &sep, &tofree);
	if (check != sep)
		return (check);
	tmp = strs;
	len = 1;
	while (*tmp)
		len += ft_strlen(*(tmp++));
	ns = malloc((len + (ft_tab_len(strs) - 1) * ft_strlen(sep)) * sizeof(char));
	if (!ns)
		return (NULL);
	*ns = 0;
	tmp = strs;
	while (*tmp)
	{
		ft_strcat(ns, *(tmp++));
		if (*tmp)
			ft_strcat(ns, sep);
	}
	ft_manage_strings(strs, sep, tofree);
	return (ns);
}
