/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:29:06 by majkijew          #+#    #+#             */
/*   Updated: 2026/01/23 18:02:36 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "minirt.h"

t_amb_light	amb_light(char *line, t_amb_light a)
{
	int		i;
	int		len;

	i = 0 + len_spaces(line);
	if (line[i] == '.')
		a.ratio = -1;
	if (!set_double(&a.ratio, line + i, &len))
		a.ratio = -1;
	i = i + len + len_spaces(line + i + len);
	if (!set_color(&a.color, line + i, &len))
		a.ratio = -1;
	i = i + len + len_spaces(line + i + len);
	if (line[i] != '\0' && line[i] != '\n')
		a.ratio = -1;
	return (a);
}

t_camera	camera(char *line, t_camera c)
{
	int			i;
	int			len;
	int			flag;

	flag = 0;
	i = 0 + len_spaces(line);
	if (!set_tuple(c.position, line + i, &len, 1))
		flag = -1;
	i = i + len + len_spaces(line + i + len);
	if (!set_tuple(c.orientation_vector, line + i, &len, 0))
		flag = -1;
	i = i + len + len_spaces(line + i + len);
	if (!is_numeric(line[i]))
		flag = -1;
	if (!set_double(&c.horizontal_field, line + i, &len))
		flag = -1;
	i = i + len + len_spaces(line + i + len);
	if ((line[i] != '\0' && line[i] != '\n') || flag == -1)
		c.horizontal_field = -1;
	return (c);
}

t_light	*light_f(char *line, t_light *l)
{
	int		i;
	int		len;

	i = 0 + len_spaces(line);
	if (!set_tuple(l->position, line + i, &len, 1))
		return (NULL);
	i = i + len + len_spaces(line + i + len);
	l->bright_ratio = atod(&line[i]);
	if (line[i] == '.')
		return (NULL);
	while (is_numeric(line[i]))
		i++;
	if (line[i - 1] == '.')
		return (NULL);
	while (ft_isspace(line[i]))
		i++;
	if (!set_color(&l->color, line + i, &len))
		return (NULL);
	i = i + len + len_spaces(line + i + len);
	if ((line[i] != '\n' && line[i] != '\0'))
		return (NULL);
	return (l);
}
