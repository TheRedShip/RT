/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:09:49 by marvin            #+#    #+#             */
/*   Updated: 2024/03/28 19:09:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char **argv)
{
	t_scene		*scene;

	if (argc != 2)
	{
		printf("Usage: %s scenes/<file.rt>\n", argv[0]);
		return (1);
	}
	scene = rt_parse(argv[1]);
	printf("Parsing successful\n");
	free(scene);
	return (0);
}
