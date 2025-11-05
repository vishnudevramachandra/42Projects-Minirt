/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_figures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:57:51 by vramacha          #+#    #+#             */
/*   Updated: 2025/11/05 18:04:30 by vramacha         ###   ########.fr       */
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
	len = set_vector(&obj->sp.pos, line + i);
	if (!len)
		return (free(obj), NULL);
	i = i + len + len_spaces(line + i + len);
	len = set_double(&obj->sp.dia, line + i);
	if (!len)
		return (free(obj), NULL);
	i = i + len + len_spaces(line + i + len);
	len = set_color(&obj->sp.color, line + i);
	if (!len)
		return (free(obj), NULL);
	return (obj);
}

t_obj	*parse_cylinder(char *line)
{
	(void)(line);
	return (NULL);
}

t_obj	*parse_plane(char *line)
{
	(void)(line);
	return (NULL);
}

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
	if (!obj || !create_node_and_add_to_list(obj, objs))
		return (ft_lstclear(objs, free), NULL);
	print_obj(*objs);
	return (*objs);
}
