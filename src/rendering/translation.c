/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 10:26:06 by vramacha          #+#    #+#             */
/*   Updated: 2026/01/30 23:08:54 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minirt.h"

static void	translate_objects_helper(t_obj *obj, t_mat4 mat)
{
	if (obj->typ == SPHERE)
		multi_mat_tuple(obj->sp.pos, mat, obj->sp.pos);
	else if (obj->typ == PLANE)
		multi_mat_tuple(obj->pl.point, mat, obj->pl.point);
	else if (obj->typ == CONE)
		multi_mat_tuple(obj->co.apex, mat, obj->co.apex);
	else if (obj->typ == CYLINDER)
		multi_mat_tuple(obj->cy.pos, mat, obj->cy.pos);
	else if (obj->typ == TEXTURE)
		translate_objects_helper(obj->tx.sub_obj, mat);
}

static void	translate_objects(t_list *node, t_mat4 mat)
{
	t_obj	*obj;

	while (node)
	{
		obj = node->content;
		translate_objects_helper(obj, mat);
		node = node->next;
	}
}

static void	translate_lights(t_list *node, t_mat4 mat)
{
	t_light	*light;

	while (node)
	{
		light = node->content;
		multi_mat_tuple(light->position, mat, light->position);
		node = node->next;
	}
}

void	translate_objects_and_lights(t_mrt *m)
{
	t_mat4	mat;
	t_tup	n_pos;

	multi_tuple(n_pos, m->scene->camera.position, -1);
	translation_mat(mat, n_pos);
	translation_mat(m->inv.trsl, m->scene->camera.position);
	translate_objects(m->obj, mat);
	translate_lights(m->scene->lights_list, mat);
	multi_mat_tuple(m->scene->camera.position, mat, m->scene->camera.position);
}
