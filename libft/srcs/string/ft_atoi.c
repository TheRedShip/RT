/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:38:15 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/11 23:50:29 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(char *nptr)
{
	long	n;
	int		sign;

	n = 0;
	sign = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		sign = (int) 2 * (0.5 - (*(nptr++) == '-'));
	while (ft_isdigit(*nptr))
		n = n * 10 + (int){*(nptr++) - '0'};
	return (sign * n);
}

static inline int	ft_index(char *str, char c)
{
	char	*tmp;

	tmp = str;
	while (*tmp && *tmp != c)
		tmp++;
	if (!tmp)
		return (0);
	return (tmp - str);
}

int	ft_atoi_base(char *nptr, int base)
{
	static char	base_s[17] = "0123456789abcdef";
	long		n;
	int			i;
	int			sign;

	n = 0;
	sign = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		sign = (int) 2 * (0.5 - (*(nptr++) == '-'));
	while (*nptr)
	{
		i = ft_index(base_s, *(nptr++));
		if (i < 0)
			return (-1);
		n = n * base + i;
	}
	return (sign * n);
}
