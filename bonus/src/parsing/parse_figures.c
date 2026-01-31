/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_figures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:57:51 by vramacha          #+#    #+#             */
/*   Updated: 2026/01/31 15:21:16 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "minirt_bonus.h"

t_obj	*parse_sphere(char *line)
{
	int		i;
	int		len;
	t_obj	*obj;

	obj = malloc(sizeof(t_obj));
	if (!obj)
		return (NULL);
	obj->typ = SPHERE;
	i = 0 + len_spaces(line);
	if (!set_tuple(obj->sp.pos, line + i, &len, 1))
		return (free(obj), NULL);
	i = i + len + len_spaces(line + i + len);
	if (!set_double(&obj->sp.dia, line + i, &len))
		return (free(obj), NULL);
	i = i + len + len_spaces(line + i + len);
	if (!set_color(&obj->sp.mt.pattern.color1, line + i, &len))
		return (free(obj), NULL);
	i = i + len + len_spaces(line + i + len);
	if (!set_pattern(&obj->sp.mt, line + i, &len))
		obj->sp.mt.pattern.fcn = NULL;
	return (obj);
}

static int	parse_cylinder_data(t_obj *obj, char *line)
{
	int		i;
	int		len;

	i = 0 + len_spaces(line);
	if (!set_tuple(obj->cy.pos, line + i, &len, 1))
		return (0);
	i = i + len + len_spaces(line + i + len);
	if (!set_tuple(obj->cy.axis, line + i, &len, 0))
		return (0);
	i = i + len + len_spaces(line + i + len);
	if (!set_double(&obj->cy.dia, line + i, &len))
		return (0);
	i = i + len + len_spaces(line + i + len);
	if (!set_double(&obj->cy.height, line + i, &len))
		return (0);
	i = i + len + len_spaces(line + i + len);
	if (!set_color(&obj->cy.mt.pattern.color1, line + i, &len))
		return (0);
	if (!set_pattern(&obj->cy.mt, line + i, &len))
		obj->cy.mt.pattern.fcn = NULL;
	return (1);
}

t_obj	*parse_cylinder(char *line)
{
	t_obj	*obj;

	obj = malloc(sizeof(t_obj));
	if (!obj)
		return (NULL);
	obj->typ = CYLINDER;
	if (!parse_cylinder_data(obj, line))
		return (free(obj), NULL);
	return (obj);
}

t_obj	*parse_plane(char *line)
{
	int		i;
	int		len;
	t_obj	*obj;

	obj = malloc(sizeof(t_obj));
	if (!obj)
		return (NULL);
	obj->typ = PLANE;
	i = 0 + len_spaces(line);
	if (!set_tuple(obj->pl.point, line + i, &len, 1))
		return (free(obj), NULL);
	i = i + len + len_spaces(line + i + len);
	if (!set_tuple(obj->pl.norm_vec, line + i, &len, 1))
		return (free(obj), NULL);
	i = i + len + len_spaces(line + i + len);
	if (!set_color(&obj->pl.mt.pattern.color1, line + i, &len))
		return (free(obj), NULL);
	i = i + len + len_spaces(line + i + len);
	if (!set_pattern(&obj->pl.mt, line + i, &len))
		obj->pl.mt.pattern.fcn = NULL;
	return (obj);
}

t_obj	*parse_cone(char *line)
{
	int		i;
	int		len;
	t_obj	*obj;

	obj = malloc(sizeof(t_obj));
	if (!obj)
		return (NULL);
	obj->typ = CONE;
	i = 0 + len_spaces(line);
	if (!set_tuple(obj->co.apex, line + i, &len, 1))
		return (free(obj), NULL);
	i = i + len + len_spaces(line + i + len);
	if (!set_double(&obj->co.dia, line + i, &len))
		return (free(obj), NULL);
	i = i + len + len_spaces(line + i + len);
	if (!set_double(&obj->co.height, line + i, &len))
		return (free(obj), NULL);
	i = i + len + len_spaces(line + i + len);
	if (!set_color(&obj->co.mt.pattern.color1, line + i, &len))
		return (free(obj), NULL);
	i = i + len + len_spaces(line + i + len);
	if (!set_pattern(&obj->co.mt, line + i, &len))
		obj->co.mt.pattern.fcn = NULL;
	init_vector(obj->co.axis, 0, 1, 0);
	return (obj);
}
