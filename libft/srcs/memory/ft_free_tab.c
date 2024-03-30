/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:55:37 by rgramati          #+#    #+#             */
/*   Updated: 2024/03/03 18:35:47 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_tab(void **tab)
{
	void	**tmp;

	tmp = tab;
	if (!tab || !tmp)
		return ;
	while (*tmp)
		free(*(tmp++));
	free(tab);
}

void	ft_free_big_tab(void **tab, int depth)
{
	void	**tmp;

	tmp = tab;
	if (!tab)
		return ;
	if (depth == 1)
	{
		free(tab);
		return ;
	}
	while (*tmp)
		ft_free_big_tab((void **)*(tmp++), depth - 1);
	free(tab);
}
