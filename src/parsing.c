/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:16:44 by majkijew          #+#    #+#             */
/*   Updated: 2025/11/03 14:19:23 by majkijew         ###   ########.fr       */
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

t_amb_light	amb_light(char *line)
{
	int		i;
	int		j;
	t_amb_light	a;

	j = 0;
	i = 0;
	while (line[i] != '\n' && ft_isspace(line[i]))
		i++;
	a.ratio = atod(&line[i]);
	while ((line[i] >= '0' && line[i] <= '9') || line[i] == '.')
		i++;
	while (ft_isspace(line[i]))
		i++;
	while (j < 3 && line[i])
	{
		set_color(&a.color, j, ft_atoi(&line[i]));
		while (line[i] >= '0' && line[i] <= '9')
			i++;
		if (line[i] == ',')
			i++;
		j++;
	}
	return (a);
}

t_camera	camera(char *line)
{
	int			i;
	int			j;
	t_camera	c;

	j = 0;
	i = 0;
	while (ft_isspace(line[i])) //idk if isspace here is not kinda redundant
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
	while (ft_isspace(line[i])) //idk if isspace here is not kinda redundant
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
	while (ft_isspace(line[i])) //idk if isspace here is not kinda redundant
		i++;
	c.horizontal_field = atod(&line[i]);
	return (c);
}

t_light	light(char *line)
{
	t_light	l;
	int		j;
	int		i;

	j = 0;
	i = 0;
	while (ft_isspace(line[i])) //idk if isspace here is not kinda redundant
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
	while (ft_isspace(line[i])) //idk if isspace here is not kinda redundant
		i++;
	l.bright_ratio = atod(&line[i]);
	while ((line[i] >= '0' && line[i] <= '9') || line[i] == '.')
		i++;
	j = 0;
	while (ft_isspace(line[i])) //idk if isspace here is not kinda redundant
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
	return (l);
}

void	read_from_fd(char *file_name)
{
	int		fd;
	int		i;
	char	*line;
	t_amb_light	*a = malloc(sizeof(t_amb_light));

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
				*a = amb_light(line + i);
				printf("%i,%i,%i\n", a->color.b, a->color.g, a->color.b);
			}
			else if (line[i] == 'C')
			{
				i++;
				camera(line + i);
			}
			else if (line[i] == 'L')
			{
				i++;
				light(line + i);
			}
			// else
			// 	geo_figures(line[i]);
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
}
