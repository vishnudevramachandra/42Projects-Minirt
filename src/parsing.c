/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:16:44 by majkijew          #+#    #+#             */
/*   Updated: 2025/11/03 21:48:41 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../Includes/minirt.h"

int	is_numeric(char c)
{
	if ((c >= '0' && c <= '9') || c == '.')
		return (1);
	return (0);
}

void	set_vector(t_vec *v, int j, double value)
{
	if (j < 1)
		v->x = value;
	else if (j < 2)
		v->y = value;
	else
		v->z = value;
}

void	set_color(t_rgb *c, int j, int value)
{
	if (j < 1)
		c->r = value;
	else if (j < 2)
		c->g = value;
	else
		c->b = value;
}

//separete for ratio and color add valuse to the struct (first make the 
//struct ofc and add check if the values are in the range)

t_amb_light	amb_light(char *line, t_amb_light a)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (line[i] != '\n' && ft_isspace(line[i]))
		i++;
	a.ratio = atod(&line[i]);
	while ((line[i] >= '0' && line[i] <= '9') || line[i] == '.')
		i++;
	while (ft_isspace(line[i]) && line[i] != '\n')
		i++;
	while (j < 3 && line[i] && line[i] != '\n')
	{
		set_color(&a.color, j, ft_atoi(&line[i]));
		while (line[i] >= '0' && line[i] <= '9')
			i++;
		if (line[i] == ',')
			i++;
		j++;
	}
	printf("ratio: %g\n", a.ratio);
	printf("colors: r=%d g=%d b=%d\n", a.color.r, a.color.g, a.color.b);
	return (a);
}

t_camera	camera(char *line, t_camera c)
{
	int			i;
	int			j;

	j = 0;
	i = 0;
	while (ft_isspace(line[i]))
		i++;
	while (j < 3 && line[i] && line[i] != '\n')
	{
		set_vector(&c.position, j, atod(&line[i]));
		while ((line[i] >= '0' && line[i] <= '9') || line[i] == '.'
			|| line[i] == '-' || line[i] == '+')
			i++;
		if (line[i] == ',')
			i++;
		j++;
	}
	j = 0;
	while (ft_isspace(line[i]))
		i++;
	while (j < 3 && line[i] && line[i] != '\n')
	{
		set_vector(&c.orientation_vector, j, atod(&line[i]));
		while ((line[i] >= '0' && line[i] <= '9') || line[i] == '.')
			i++;
		if (line[i] == ',')
			i++;
		j++;
	}
	while (ft_isspace(line[i]))
		i++;
	c.horizontal_field = atod(&line[i]);
	printf("position: x=%g y=%g z=%g\n", c.position.x, c.position.y, c.position.z);
	printf("orientation: x=%g y=%g z=%g\n", c.orientation_vector.x, c.orientation_vector.y, c.orientation_vector.z);
	printf("horizontal field %g\n", c.horizontal_field);
	return (c);
}

t_light	light(char *line, t_light l)
{
	int		j;
	int		i;

	j = 0;
	i = 0;
	printf("");
	while (ft_isspace(line[i]))
		i++;
	while (j < 3 && line[i] && line[i] != '\n')
	{
		set_vector(&l.position, j, atod(&line[i]));
		while ((line[i] >= '0' && line[i] <= '9') || line[i] == '.'
			|| line[i] == '-' || line[i] == '+')
			i++;
		if (line[i] == ',')
			i++;
		j++;
	}
	while (ft_isspace(line[i]))
		i++;
	l.bright_ratio = atod(&line[i]);
	while ((line[i] >= '0' && line[i] <= '9') || line[i] == '.')
		i++;
	j = 0;
	while (ft_isspace(line[i]))
		i++;
	while (j < 3 && line[i])
	{
		set_color(&l.color, j, ft_atoi(&line[i]));
		while (line[i] >= '0' && line[i] <= '9')
			i++;
		if (line[i] == ',')
			i++;
		j++;
	}
	printf("light pos: x=%g, y=%g, z=%g\n", l.position.x, l.position.y, l.position.z);
	printf("brightness ratio: %g\n", l.bright_ratio);
	printf("colors: r=%d g=%d b=%d\n", l.color.r, l.color.g, l.color.b);
	return (l);
}

bool	scene_range(t_amb_light a, t_camera c, t_light l)
{
	if (a.ratio < 0 || a.ratio > 1)
		return (false);
	else if ((a.color.r < 0 || a.color.r > 255) || (a.color.g < 0
			|| a.color.g > 255) || (a.color.b < 0 || a.color.b > 255))
		return (false);
	else if (c.position.x == NAN || c.position.y == NAN || c.position.z == NAN)
		return (false);
	else if ((c.orientation_vector.x < -1 || c.orientation_vector.x > 1)
		|| (c.orientation_vector.y < -1 || c.orientation_vector.y > 1)
		|| (c.orientation_vector.z < -1 || c.orientation_vector.z > 1))
		return (false);
	else if (c.horizontal_field < 0 || c.horizontal_field > 180)
		return (false);
	else if (l.position.x == NAN || l.position.y == NAN || l.position.z == NAN)
		return (false);
	else if (l.bright_ratio < 0 || l.bright_ratio > 1)
		return (false);
	else if ((l.color.r < 0 || l.color.r > 255) || (l.color.g < 0
			|| l.color.g > 255) || (l.color.b < 0 || l.color.b > 255))
		return (false);
	else
		return (true);
}

void	read_from_fd(char *file_name, t_scene *scene)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		erro_msg("ERROR", 1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		i = 0;
		while (line[i])
		{
			if (line[i] == 'A')
			{	
				i++;
				scene->amb_light = amb_light(line + i, scene->amb_light);
			}
			else if (line[i] == 'C')
			{
				i++;
				scene->camera = camera(line + i, scene->camera);
			}
			else if (line[i] == 'L')
			{
				i++;
				scene->light = light(line + i, scene->light);
			}
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
	if (scene_range(scene->amb_light, scene->camera, scene->light) == false)
		erro_msg("INCORRECT RANGE", STDERR_FILENO); // free and exit
	//if everything is correct with that part procceed to parse the figures
	printf("great success\n");
}
