/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:11:16 by marvin            #+#    #+#             */
/*   Updated: 2024/03/28 19:11:16 by marvin           ###   ########.fr       */
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
	if (ft_strncmp(line, "A\t", 2) == 0 && rt_verify_ambient(line))
		return (rt_parse_ambient(line, scene));
	else if (ft_strncmp(line, "C\t", 2) == 0 && rt_verify_camera(line))
		return (rt_parse_camera(line, scene));
	else if (ft_strncmp(line, "L\t", 2) == 0 && rt_verify_light(line))
		return (rt_parse_light(line, scene));
	else if (ft_strncmp(line, "sp\t", 3) == 0 && rt_verify_sphere(line))
		return (rt_parse_sphere(line, scene));
	else if (ft_strncmp(line, "pl\t", 3) == 0 && rt_verify_plane(line))
		return (rt_parse_plane(line, scene));
	else if (ft_strncmp(line, "cy\t", 3) == 0 && rt_verify_cylinder(line))
		return (rt_parse_cylinder(line, scene));
	else
	{
		if (line[0] != '\r')
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