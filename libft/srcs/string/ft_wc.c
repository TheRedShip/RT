/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 11:58:19 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/18 23:35:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_wc(char *str, char delim)
{
	int	i;
	int	wc;

	i = 0;
	if (!*str)
		return (0);
	wc = (*str != delim);
	while (str[++i])
	{
		if (str[i - 1] == delim && str[i] != delim)
			wc++;
	}
	return (wc);
}
