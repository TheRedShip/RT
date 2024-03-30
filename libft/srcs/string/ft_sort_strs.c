/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_strs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:51:35 by rgramati          #+#    #+#             */
/*   Updated: 2024/03/03 18:54:59 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swap_strs(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_sort_strs_tab(char **tab, int size)
{
	int	min;
	int	curr;
	int	swp;
	int	len;

	curr = 0;
	while (curr <= size)
	{
		min = curr;
		swp = curr + 1;
		while (swp <= size - 1)
		{
			len = ft_strlen(*(tab + swp)) + 1;
			if (ft_strncmp(*(tab + swp), *(tab + min), len) < 0)
				min = swp;
			swp++;
		}
		ft_swap_strs(tab + curr, tab + min);
		curr++;
	}
}

void	ft_sort_lowstrs_tab(char **tab, int size)
{
	int		min;
	int		curr;
	int		swp;
	char	*low_s;
	char	*low_m;

	curr = 0;
	while (curr <= size)
	{
		min = curr;
		swp = curr + 1;
		while (swp <= size - 1)
		{
			low_s = ft_strlow(*(tab + swp));
			low_m = ft_strlow(*(tab + min));
			if (ft_strncmp(low_s, low_m, ft_strlen(low_s) + 1) < 0)
				min = swp;
			swp++;
			free(low_s);
			free(low_m);
		}
		ft_swap_strs(tab + curr, tab + min);
		curr++;
	}
}
