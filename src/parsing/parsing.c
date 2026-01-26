/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:16:44 by majkijew          #+#    #+#             */
/*   Updated: 2026/01/26 19:01:05 by vramacha         ###   ########.fr       */
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
		return (ft_lstclear(lights, free), NULL);
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
		scene->lights_list = parse_lights(line, &scene->lights_list);
}

void	read_from_fd(char *file_name, t_scene *scene, t_list **objs)
{
	int		fd;
	char	*line;
	int		i;

	*objs = NULL;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		erro_msg("ERROR", 1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		i = 0 + len_spaces(line);
		if (line[i] == '\n')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (verify_id(line) == false)
		{
			free(line);
			erro_msg("INCORRECT RANGE", STDERR_FILENO); // free and exit
		}
		if (is_scene(line + i))
		{
			fill_scene(scene, line + i);
		}
		else if (!is_object(line + i) || !parse_obj(line + i, objs))
		{
			free(line);
			erro_msg("ERROR here?", STDERR_FILENO);
		}
		if (line)
			free(line);
		line = get_next_line(fd);
	}
	// if (*objs)
	// 	print_obj(*objs);
	close(fd);
	if (scene_range(scene->amb_light, scene->camera) == false)
		erro_msg("INCORRECT RANGE", STDERR_FILENO); // free and exit
	// //if everything is correct with that part procceed to parse the figures
	printf("great success\n");
}
// printf("great success\n");
