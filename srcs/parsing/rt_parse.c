/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:11:16 by marvin            #+#    #+#             */
/*   Updated: 2024/05/02 14:23:24 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		is_file_valid(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		printf("Error: Cannot open file\n");
		return (0);
	}
	close(fd);
	if (ft_strncmp((file_name + ft_strlen(file_name)) - 3, ".rt", 3))
	{
		printf("Error: Wrong file format\n");
		return (0);
	}
	if (access(file_name, R_OK) == -1)
	{
		printf("Error: Missing permissions\n");
		return (0);
	}
	return (1);
}

int		rt_verify_parsing(char *line, t_scene **scene)
{
	if (ft_strncmp(line, "A\t", 2) == 0 && rt_verify_ambient(*scene, line))
		return (rt_parse_ambient(line, scene));
	else if (ft_strncmp(line, "C\t", 2) == 0 && rt_verify_camera(*scene, line))
		return (rt_parse_camera(line, scene));
	else if (ft_strncmp(line, "L\t", 2) == 0 && rt_verify_light(*scene, line))
		return (rt_parse_light(line, scene));
	else if (ft_strncmp(line, "B\t", 2) == 0 && rt_verify_bloom(*scene, line))
		return (rt_parse_bloom(line, scene));
	else if (ft_strncmp(line, "sp\t", 3) == 0 && rt_verify_sphere(line))
		return (rt_parse_sphere(line, scene));
	else if (ft_strncmp(line, "pl\t", 3) == 0 && rt_verify_plane(line))
		return (rt_parse_plane(line, scene));
	else if (ft_strncmp(line, "cy\t", 3) == 0 && rt_verify_cylinder(line))
		return (rt_parse_cylinder(line, scene));
	else if (ft_strncmp(line, "ls\t", 3) == 0 && rt_verify_lightsphere(line))
		return (rt_parse_lightsphere(line, scene));
	else if (ft_strncmp(line, "lq\t", 3) == 0 && rt_verify_lightquad(line))
		return (rt_parse_lightquad(line, scene));
	else if (ft_strncmp(line, "gs\t", 3) == 0 && rt_verify_glasssphere(line))
		return (rt_parse_glasssphere(line, scene));
	else if (ft_strncmp(line, "qd\t", 3) == 0 && rt_verify_quad(line))
		return (rt_parse_quad(line, scene));
	else if (ft_strncmp(line, "cu\t", 3) == 0 && rt_verify_cube(line))
		return (rt_parse_cube(line, scene));
	else if (ft_strncmp(line, "gc\t", 3) == 0 && rt_verify_glasscube(line))
		return (rt_parse_glasscube(line, scene));
	else if (ft_strncmp(line, "el\t", 3) == 0 && rt_verify_ellipse(line))
		return (rt_parse_ellipse(line, scene));
	else if (ft_strncmp(line, "po\t", 2) == 0 && rt_verify_portal(line))
		return (rt_parse_portal(line, scene));
	else
	{
		if ((line[0] != '\r' && line[0] != '\n') && line[0] != '#')
			return (0);
	}
	return (1);
}

void	rt_exit_parsing(char *line, t_scene *scene, int fd)
{
	if (line)
	{
		printf("Error: Parsing failed : %s\n", line);
		free(line);
	}
	if (fd != -1)
		close(fd);
	rt_free_scene(scene);
}

void	rt_parse(char *file, t_scene **scene)
{
	int		fd;
	char	*line;

	if (!is_file_valid(file))
		rt_exit_parsing(NULL, *scene, -1);
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (!rt_verify_parsing(line, scene))
			rt_exit_parsing(line, *scene, fd);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
