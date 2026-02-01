/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 10:38:45 by vramacha          #+#    #+#             */
/*   Updated: 2026/02/01 17:41:06 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	project_objects_helper(t_obj *obj, t_mat4 mat)
{
	t_tup	tup;

	if (obj->typ == SPHERE)
		copy_tup(obj->sp.pos, *multi_mat_tuple(tup, mat, obj->sp.pos));
	else if (obj->typ == PLANE)
	{
		copy_tup(obj->pl.point, *multi_mat_tuple(tup, mat, obj->pl.point));
		copy_tup(obj->pl.norm_vec,
			*multi_mat_tuple(tup, mat, obj->pl.norm_vec));
	}
	else if (obj->typ == CONE)
		copy_tup(obj->co.apex, *multi_mat_tuple(tup, mat, obj->co.apex));
	else if (obj->typ == CYLINDER)
	{
		copy_tup(obj->cy.pos, *multi_mat_tuple(tup, mat, obj->cy.pos));
		copy_tup(obj->cy.axis, *multi_mat_tuple(tup, mat, obj->cy.axis));
	}
	else if (obj->typ == TEXTURE)
		project_objects_helper(obj->tx.sub_obj, mat);
}

void	project_objects(t_list *node, t_mat4 mat)
{
	t_obj	*obj;

	while (node)
	{
		obj = node->content;
		project_objects_helper(obj, mat);
		node = node->next;
	}
}

static void	project_lights(t_list *node, t_mat4 mat)
{
	t_light	*light;
	t_tup	tmp;

	while (node)
	{
		light = node->content;
		multi_mat_tuple(tmp, mat, light->position);
		copy_tup(light->position, tmp);
		node = node->next;
	}
}

// project objects on to camera's axes. This is done so that the objects in the
// same direction as camera's orientation vector are now in front of the camera.
void	project_objects_and_lights(t_mrt *m)
{
	t_mat4	mat;
	t_mat4	inv_mat;

	identity_mat(mat);
	if (__DBL_EPSILON__ < (dot_prod(m->scene->camera.orientation_vector,
				m->scene->camera.orientation_vector) - 1))
		normalize(m->scene->camera.orientation_vector);
	copy_vector(mat[2], m->scene->camera.orientation_vector);
	cross_prod(mat[0], (t_tup){0, 1, 0}, mat[2]);
	if (dot_prod(mat[0], mat[0]) == 0)
	{
		if (0 < mat[2][1])
			cross_prod(mat[0], (t_tup){0, 0, -1}, mat[2]);
		else
			cross_prod(mat[0], (t_tup){0, 0, 1}, mat[2]);
	}
	normalize(mat[0]);
	cross_prod(mat[1], mat[2], mat[0]);
	project_objects(m->obj, mat);
	project_lights(m->scene->lights_list, mat);
	transpose_mat(*copy_mat(m->inv.proj, mat));
	multi_mat_mat(inv_mat, m->inv.trsl, m->inv.proj);
	multi_mat_mat(mat, m->inv.final, inv_mat);
	copy_mat(m->inv.final, mat);
	copy_vector(m->scene->camera.orientation_vector, (t_tup){0, 0, 1});
}
