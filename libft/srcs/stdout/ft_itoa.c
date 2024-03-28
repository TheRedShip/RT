/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:10:27 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/19 16:40:23 by ycontre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_sizelen_n(int n)
{
	int	cpt;

	cpt = 1;
	if (n == -2147483648)
	{
		cpt = 11;
		return (cpt);
	}
	if (n < 0)
	{
		cpt++;
		n *= -1;
	}
	while (n > 9)
	{
		cpt++;
		n /= 10;
	}
	return (cpt);
}

static char	*ft_itoa_rec(int n, char **str)
{
	if (n == -2147483648)
	{
		ft_strlcat(*str, "-2147483648", 12, 1);
		*str += 12;
		return (*str);
	}
	if (n < 0)
	{
		**str = '-';
		n = n * -1;
		(*str)++;
	}
	if (n < 10)
		**str = n + 48;
	else
	{
		ft_itoa_rec(n / 10, str);
		**str = n % 10 + 48;
	}
	(*str)++;
	return (*str);
}

char	*ft_itoa(int n)
{
	char	*str;
	char	*start;

	str = ft_calloc((ft_sizelen_n(n) + 1), sizeof(char));
	if (!str)
		return (NULL);
	start = str;
	ft_itoa_rec(n, &str);
	return (start);
}
