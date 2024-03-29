/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:09:30 by marvin            #+#    #+#             */
/*   Updated: 2024/03/28 19:09:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>

typedef struct	s_veci3
{
	int		x;
	int		y;
	int		z;
}				t_veci3;

typedef struct	s_vecf3
{
	float	x;
	float	y;
	float	z;
}				t_vecf3;

# include "parsing.h"
# include "libft.h"


#endif