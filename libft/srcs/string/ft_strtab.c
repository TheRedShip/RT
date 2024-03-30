/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 21:35:11 by rgramati          #+#    #+#             */
/*   Updated: 2024/03/03 15:31:01 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strtab(char *str)
{
	char	**tab;

	tab = malloc(2 * sizeof(char *));
	*tab = str;
	*(tab + 1) = NULL;
	return (tab);
}

void	ft_strtabjoin(char ***tab, char **next)
{
	char	**tmp;

	tmp = next;
	if (!tmp)
		return ;
	while (*tmp)
		ft_strapp(tab, *(tmp++));
	free(next);
}

void	ft_strapp(char ***tab, char *str)
{
	char	**tmp;
	char	**ttmp;
	char	**res;

	tmp = *tab;
	while (tmp && *tmp)
		tmp++;
	res = malloc((tmp - *tab + 2) * sizeof(char *));
	tmp = *tab;
	ttmp = res;
	while (tmp && *tmp)
		*(ttmp++) = *(tmp++);
	*(ttmp++) = str;
	*ttmp = 0;
	free(*tab);
	*tab = res;
}
