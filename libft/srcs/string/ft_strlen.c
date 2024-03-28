/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:37:02 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/30 18:56:48 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(char *str)
{
	char	*tmp;

	if (!str || !*str)
		return (0);
	tmp = str;
	while (tmp && *tmp)
		tmp++;
	return (tmp - str);
}
