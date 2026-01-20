/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_figures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:57:51 by vramacha          #+#    #+#             */
/*   Updated: 2026/01/20 22:09:33 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
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
	if (!set_vector(obj->sp.pos, line + i, &len))
		return (free(obj), NULL);
	obj->sp.pos[3] = 1;
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

t_obj	*parse_cylinder(char *line)
{
	int		i;
	int		len;
	t_obj	*obj;

	obj = malloc(sizeof(t_obj));
	if (!obj)
		return (NULL);
	obj->typ = CYLINDER;
	i = 0 + len_spaces(line);
	if (!set_vector(obj->cy.pos, line + i, &len))
		return (free(obj), NULL);
	i = i + len + len_spaces(line + i + len);
	if (!set_vector(obj->cy.axis, line + i, &len))
		return (free(obj), NULL);
	i = i + len + len_spaces(line + i + len);
	if (!set_double(&obj->cy.dia, line + i, &len))
		return (free(obj), NULL);
	i = i + len + len_spaces(line + i + len);
	if (!set_double(&obj->cy.height, line + i, &len))
		return (free(obj), NULL);
	i = i + len + len_spaces(line + i + len);
	if (!set_pattern(&obj->cy.mt, line + i, &len))
		obj->cy.mt.pattern.fcn = NULL;
	return (obj);
}

// if (!set_color(&obj->cy.mt.pattern.color1, line + i, &len))
	// 	return (free(obj), NULL);
	// obj->cy.mt.pattern.fcn = NULL;
	// obj->cy.mt.shininess = 100;

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
	if (!set_vector(obj->pl.point, line + i, &len))
		return (free(obj), NULL);
	i = i + len + len_spaces(line + i + len);
	if (!set_vector(obj->pl.norm_vec, line + i, &len))
		return (free(obj), NULL);
	i = i + len + len_spaces(line + i + len);
	if (!set_color(&obj->pl.mt.pattern.color1, line + i, &len))
		return (free(obj), NULL);
	i = i + len + len_spaces(line + i + len);
	if (!set_pattern(&obj->pl.mt, line + i, &len))
		obj->pl.mt.pattern.fcn = NULL;
	return (obj);
}
// obj->pl.mt.pattern.color2 = (t_rgb){0, 0, 0};
// init_vector(obj->pl.mt.pattern.param, 0.5, 0.5, 0.5);
// obj->pl.mt.pattern.fcn = checker_pattern;
// obj->pl.mt.shininess = 10;

int	create_node_and_add_to_list(void *content, t_list **lst)
{
	t_list	*node;

	node = ft_lstnew(content);
	if (!node)
		return (0);
	ft_lstadd_back(lst, node);
	return (1);
}

t_list	*parse_obj(char *line, t_list **objs)
{
	t_obj	*obj;

	if (line[0] == 's' && line[1] == 'p')
		obj = parse_sphere(line + 2);
	else if (line[0] == 'c' && line[1] == 'y')
		obj = parse_cylinder(line + 2);
	else
		obj = parse_plane(line + 2);
	if (!obj)
		return (ft_lstclear(objs, free), NULL);
	if (!create_node_and_add_to_list(obj, objs))
		return (free(obj), ft_lstclear(objs, free), NULL);
	return (*objs);
}
