/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:16:44 by majkijew          #+#    #+#             */
/*   Updated: 2026/01/23 18:50:34 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "minirt.h"
#include "parse.h"


bool	scene_range(t_amb_light a, t_camera c)
{
	if (a.ratio < 0 || a.ratio > 1)
		return (false);
	else if ((a.color.r < 0 || a.color.r > 255) || (a.color.g < 0
			|| a.color.g > 255) || (a.color.b < 0 || a.color.b > 255))
		return (false);
	// else if ((*c.orientation_vector < -1 || *c.orientation_vector > 1))
	// 	return (false);
	else if (c.horizontal_field < 0 || c.horizontal_field > 180)
		return (false);
	else
		return (true);
}

static char	*get_identifier(char *line)
{
	int		i;
	int		start;
	int		len;
	char	*id;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] == '\n' || line[i] == '\0')
		return (NULL);
	start = i;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	len = i - start;
	id = malloc(len + 1);
	if (!id)
		return (NULL);
	ft_strlcpy(id, line + start, len + 1);
	id[len] = '\0';
	return (id);
}

bool	verify_id(char *line)
{
	char	*id;
	bool	valid;

	valid = false;
	id = get_identifier(line);
	if (!id)
		return (false);
	if (ft_strcmp(id, "A") == 0
		|| ft_strcmp(id, "C") == 0
		|| ft_strcmp(id, "L") == 0
		|| ft_strcmp(id, "sp") == 0
		|| ft_strcmp(id, "pl") == 0
		|| ft_strcmp(id, "co") == 0
		|| ft_strcmp(id, "cy") == 0)
		valid = true;
	free(id);
	return (valid);
}

int	is_scene(char *line)
{
	if ((line[0] == 'A' && line[1] == ' ')
		|| (line[0] == 'C' && line[1] == ' ')
		|| (line[0] == 'L' && line[1] == ' '))

		return (1);
	return (0);
}

int	is_object(char *line)
{
	if ((line[0] == 's' && line[1] == 'p' && line[2] == ' ')
		|| (line[0] == 'c' && line[1] == 'y' && line[2] == ' ')
		|| (line[0] == 'p' && line[1] == 'l' && line[2] == ' ')
		|| (line[0] == 'c' && line[1] == 'o' && line[2] == ' '))
		return (1);
	return (0);
}

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
			// free(line);
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
	//if everything is correct with that part procceed to parse the figures
	printf("great success\n");
}
