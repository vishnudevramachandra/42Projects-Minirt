/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:29:06 by majkijew          #+#    #+#             */
/*   Updated: 2026/01/31 17:06:29 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "minirt.h"

int	amb_light(char *line, t_amb_light *a)
{
	int		i;
	int		len;

	a->count++;
	if (a->count > 1)
		return (0);
	i = 0 + len_spaces(line);
	if (line[i] == '.')
		return (0);
	if (!set_double(&a->ratio, line + i, &len))
		return (0);
	if (a->ratio < 0.05)
		a->ratio = 0.05;
	i = i + len + len_spaces(line + i + len);
	if (!set_color(&a->color, line + i, &len))
		return (0);
	i = i + len + len_spaces(line + i + len);
	if ((line[i] != '\0' && line[i] != '\n'))
		a->ratio = -1;
	return (1);
}

int	camera(char *line, t_camera *c)
{
	int			i;
	int			len;

	c->count++;
	if (c->count > 1)
		return (0);
	i = 0 + len_spaces(line);
	if (c->horizontal_field != -1)
		return (0);
	if (!set_tuple(c->position, line + i, &len, 1))
		return (0);
	i = i + len + len_spaces(line + i + len);
	if (!set_tuple(c->orientation_vector, line + i, &len, 0))
		return (0);
	i = i + len + len_spaces(line + i + len);
	if (!is_numeric(line[i]))
		return (0);
	if (!set_double(&c->horizontal_field, line + i, &len))
		return (0);
	i = i + len + len_spaces(line + i + len);
	if (line[i] != '\0' && line[i] != '\n')
		return (0);
	return (1);
}

t_light	*light_f(char *line, t_light *l)
{
	int		i;
	int		len;

	l->count++;
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
