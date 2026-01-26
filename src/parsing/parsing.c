/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:16:44 by majkijew          #+#    #+#             */
/*   Updated: 2026/01/25 19:20:23 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parse.h"

t_list	*parse_lights(char *line, t_list **lights)
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	if (!light)
		return (ft_lstclear(lights, free), NULL);
	if (!light_f(line + 1, light))
		return (free(light), ft_lstclear(lights, free), NULL);
	if (!create_node_and_add_to_list(light, lights))
		return (free(light), ft_lstclear(lights, free), NULL);
	return (*lights);
}

void	fill_scene(t_scene *scene, char *line)
{
	if (line[0] == 'A')
		scene->amb_light = amb_light(line + 1, scene->amb_light);
	else if (line[0] == 'C')
		scene->camera = camera(line + 1, scene->camera);
	else if (line[0] == 'L')
		parse_lights(line, &scene->lights_list);
}

int	validate_line(char *line, t_scene *scene, t_list **objs)
{
	if (*line == '\n')
		return (1);
	if (verify_id(line) == false)
		return (0);
	if (is_scene(line))
		fill_scene(scene, line);
	else if (!is_object(line) || !parse_obj(line, objs))
		return (0);
	return (1);
}

int	read_from_fd(char *file_name, t_scene *scene, t_list **objs)
{
	int		fd;
	char	*line;
	int		i;

	*objs = NULL;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line != NULL)
	{
		i = 0 + len_spaces(line);
		if (!validate_line(line + i, scene, objs))
		{
			close(fd);
			return (0);
		}
		if (line)
			free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (scene_range(scene->amb_light, scene->camera) == false)
		return (0);
	return (1);
}
// printf("great success\n");
