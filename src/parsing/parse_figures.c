/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_figures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:57:51 by vramacha          #+#    #+#             */
/*   Updated: 2026/01/28 12:33:55 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "minirt.h"

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

static t_obj	*parse_cylinder(char *line)
{
	int		i;
	int		len;
	t_obj	*obj;

	obj = malloc(sizeof(t_obj));
	if (!obj)
		return (NULL);
	obj->typ = CYLINDER;
	i = 0 + len_spaces(line);
	if (!set_tuple(obj->cy.pos, line + i, &len, 1))
		return (free(obj), NULL);
	i = i + len + len_spaces(line + i + len);
	if (!set_tuple(obj->cy.axis, line + i, &len, 0))
		return (free(obj), NULL);
	i = i + len + len_spaces(line + i + len);
	if (!set_double(&obj->cy.dia, line + i, &len))
		return (free(obj), NULL);
	i = i + len + len_spaces(line + i + len);
	if (!set_double(&obj->cy.height, line + i, &len))
		return (free(obj), NULL);
	i = i + len + len_spaces(line + i + len);
	if (!set_color(&obj->cy.mt.pattern.color1, line + i, &len))
		return (free(obj), NULL);
	i = i + len + len_spaces(line + i + len);
	if (!set_pattern(&obj->cy.mt, line + i, &len))
		obj->cy.mt.pattern.fcn = NULL;
	return (obj);
}

static t_obj	*parse_plane(char *line)
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

static t_obj	*parse_cone(char *line)
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
	return (obj);
}

t_list	*parse_obj(char *line, t_list **objs)
{
	t_obj	*obj;

	if (line[0] == 's' && line[1] == 'p')
		obj = parse_sphere(line + 2);
	else if (line[0] == 'c' && line[1] == 'y')
		obj = parse_cylinder(line + 2);
	else if (line[0] == 'c' && line[1] == 'o')
		obj = parse_cone(line + 2);
	else if (line[0] == 'p' && line[1] == 'l')
		obj = parse_plane(line + 2);
	else if (line[0] == 't' && line[1] == 'x')
		obj = parse_texture(line + 2, REGULAR);
	else
		obj = parse_texture(line + 2, BUMP);
	if (!obj)
		return (ft_lstclear(objs, free), NULL);
	if (!create_node_and_add_to_list(obj, objs))
		return (free(obj), ft_lstclear(objs, free), NULL);
	return (*objs);
}
