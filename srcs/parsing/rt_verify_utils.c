/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_verify_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 21:47:58 by marvin            #+#    #+#             */
/*   Updated: 2024/05/07 21:47:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rt_verify_material(char *str)
{
	char		**split;

	split = ft_split(str, ',');
	if (!split || (ft_tab_len(split) != 3 && \
		ft_tab_len(split) != 2 && ft_tab_len(split) != 4))
		return (rt_return (split));
	if (rt_range_atof(split[0], 0.0, 1.0) == -1)
		return (rt_return (split));
	if (rt_range_atof(split[1], 0.0, 1.0) == -1)
		return (rt_return (split));
	ft_free_tab((void **)(split));
	return (1);
}
