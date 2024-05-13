/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:20:17 by rgramati          #+#    #+#             */
/*   Updated: 2024/05/13 18:12:32 by ycontre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static float	after_point(char *nptr, float res, int index)
{
	int	e;

	e = 0;
	while (ft_isdigit(nptr[index]))
	{
		res = (res * 10.) + (nptr[index] - '0');
		index++;
		e--;
	}
	while (e < 0)
	{
		res /= 10.;
		e++;
	}
	return (res);
}

float	ft_atof(char *nptr)
{
	int		i;
	int		sign;
	float	res;

	i = 0;
	sign = 1;
	res = 0.0;
	while (nptr[i] == 32)
		i++;
	if (nptr[i] == '-')
		sign *= -1;
	i += (nptr[i] == '+' || nptr[i] == '-');
	while (ft_isdigit(nptr[i]))
	{
		res = (res * 10.) + (nptr[i] - '0');
		i++;
	}
	if (nptr[i] != '.')
		return (res * sign);
	res = after_point(nptr, res, ++i);
	return (res * sign);
}
