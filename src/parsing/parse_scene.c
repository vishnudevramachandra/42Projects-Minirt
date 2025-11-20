/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:29:06 by majkijew          #+#    #+#             */
/*   Updated: 2025/11/20 21:58:48 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "minirt.h"

// if there is no 3 arg the horizontal field is 0 wich is obv wrong!! in camera
// i can add a check if there is ditig in atod to fix it 
//  L -40,0,30 0.7 255,255,255, accept this and it shouldnt and i think most of
// them when u have a coupe of args separeted with, would accept it not good!

t_amb_light	amb_light(char *line, t_amb_light a)
{
	int		i;
	int		len;

	i = 0;
	while (line[i] != '\n' && ft_isspace(line[i]))
		i++;
	a.ratio = atod(&line[i]);
	while ((line[i] >= '0' && line[i] <= '9') || line[i] == '.')
		i++;
	while (ft_isspace(line[i]))
		i++;
	set_color(&a.color, line + i, &len);
	while (ft_isspace(line[i]))
		i++;
	// if (line[i] != '\n' && line[i] != '\0')
	// 	a.ratio = -1;
	printf("ratio: %g\n", a.ratio);
	printf("colors: r=%d g=%d b=%d\n", a.color.r, a.color.g, a.color.b);
	return (a);
}
// printf("ratio: %g\n", a.ratio);
// printf("colors: r=%d g=%d b=%d\n", a.color.r, a.color.g, a.color.b);

//if C exists it should have 4 parametes no more no less 

t_camera	camera(char *line, t_camera c)
{
	int			i;
	int			len;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	set_vector(c.position, line + i, &len);
	i = i + len + len_spaces(line + i + len);
	set_vector(c.orientation_vector, line + i, &len);
	while (ft_isspace(line[i]))
		i++;
	c.horizontal_field = atod(&line[i]);
	while ((line[i] >= '0' && line[i] <= '9') || line[i] == '.')
		i++;
	while (ft_isspace(line[i]))
		i++;
	// if (line[i] != '\n' && line[i] != '\0')
	// 	c.horizontal_field = -1;
	// printf("position: x=%g y=%g z=%g\n", c.position.x, c.position.y, c.position.z);
	// printf("orientation: x=%g y=%g z=%g\n", c.orientation_vector.x, c.orientation_vector.y, c.orientation_vector.z);
	// printf("horizontal field %g\n", c.horizontal_field);
	return (c);
}
// printf("position: x=%g y=%g z=%g\n", c.position.x, c.position.y, c.position.z);
// printf("orientation: x=%g y=%g z=%g\n", c.orientation_vector.x, c.orientation_vector.y, c.orientation_vector.z);
// printf("horizontal field %g\n", c.horizontal_field);

//if L exists it should have 3 parametes no more no less 
t_light	light(char *line, t_light l)
{
	int		i;
	int		len;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	set_vector(l.position, line + i, &len);
	i = i + len + len_spaces(line + i + len);
	l.bright_ratio = atod(&line[i]);
	while ((line[i] >= '0' && line[i] <= '9') || line[i] == '.')
		i++;
	while (ft_isspace(line[i]))
		i++;
	set_color(&l.color, line + i, &len);
	while (ft_isspace(line[i]))
		i++;
	// if (line[i] != '\n' && line[i] != '\0')
	// 	l.bright_ratio = -1;
	// printf("light pos: x=%g, y=%g, z=%g\n", l.position.x, l.position.y, l.position.z);
	// printf("brightness ratio: %g\n", l.bright_ratio);
	// printf("colors: r=%d g=%d b=%d\n", l.color.r, l.color.g, l.color.b);
	return (l);
}
