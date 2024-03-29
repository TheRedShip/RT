/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:20:17 by rgramati          #+#    #+#             */
/*   Updated: 2024/03/28 23:04:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

double	ft_atof(char *str, int d)
{
	double	n;
	double	sum;
	double	rest;

	sum = *str - '0';
	if (d == 0)
	{
		n = ft_atoi(str);
		if (n < 0)
		{
			rest = ft_atof(str + (ft_strchr(str, '.') - str) + 1, d + 1);
			return (n - 0.1 * rest);
		}
		else
		{
			rest = ft_atof(str + (ft_strchr(str, '.') - str) + 1, d + 1);
			return (n + 0.1 * rest);
		}
	}
	if (ft_strlen(str) == 1)
		return ((double)(*str - '0'));
	if (*str == '.')
		return (ft_atof(str + 1, d + 1));
	return (sum + 0.1 * ft_atof(str + 1, d + 1));
}
