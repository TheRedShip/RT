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

#include "parsing.h"

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

int		rt_verify_parsing(char *line)
{
	if (ft_strncmp(line, "A\t", 2) == 0)
		return (rt_verify_ambient(line));
	else if (ft_strncmp(line, "C\t", 2) == 0)
		return (rt_verify_camera(line));
	else if (ft_strncmp(line, "L\t", 2) == 0)
		return (rt_verify_light(line));
	else if (ft_strncmp(line, "sp\t", 3) == 0)
		return (rt_verify_sphere(line));
	else if (ft_strncmp(line, "pl\t", 3) == 0)
		return (rt_verify_plane(line));
	else if (ft_strncmp(line, "cy\t", 3) == 0)
		return (rt_verify_cylinder(line));
	else
	{
		if (line[0] != '\r')
			return (0);
	}
	return (1);
}

void	*rt_exit_parsing(char *line, t_scene *scene, int fd)
{
	printf("Error: Parsing failed : %s\n", line);
	if (scene->ambient_light)
		free(scene->ambient_light);
	if (scene->camera)
		free(scene->camera);
	if (scene->lights)
		free(scene->lights);
	if (scene->objects)
	{
		if (scene->objects->sphere)
			free(scene->objects->sphere);
		if (scene->objects->plane)
			free(scene->objects->plane);
		if (scene->objects->cylinder)
			free(scene->objects->cylinder);
		free(scene->objects);
	}
	free(scene);
	free(line);
	close(fd);
	return (NULL);
}

t_scene *rt_parse(char *file)
{
	int		fd;
	char	*line;
	t_scene	*scene;

	if (!is_file_valid(file))
		return (0);
	scene = ft_calloc(1, sizeof(t_scene));
	if (!scene)
		return (0);
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (!rt_verify_parsing(line))
			return rt_exit_parsing(line, scene, fd);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (scene);
}