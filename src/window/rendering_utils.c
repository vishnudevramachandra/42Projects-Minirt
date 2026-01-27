/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 21:10:10 by vramacha          #+#    #+#             */
/*   Updated: 2026/01/27 14:47:42 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minirt.h"

// those vectors that are supposed to be normal vectors are normalized
void	normalize_vectors(t_mrt *m)
{
	t_list	*cur;
	t_obj	*obj;
	t_tup	vec;
	t_tup	origin;

	init_point(origin, 0, 0, 0);
	normalize(m->scene->camera.orientation_vector);
	if (!m->obj)
		return ;
	cur = m->obj;
	while (cur)
	{
		obj = cur->content;
		if (obj->typ == PLANE)
		{
			normalize(obj->pl.norm_vec);
			if (0 < dot_prod(
					*perpvec_to_plane(vec, &obj->pl, (double [4]){0, 0, 0, 1}),
				obj->pl.norm_vec))
				multi_tuple(obj->pl.norm_vec, obj->pl.norm_vec, -1);
		}
		else if (obj->typ == CYLINDER)
			normalize(obj->cy.axis);
		else if (obj->typ == CONE)
		{
			init_vector(obj->co.axis, 0, 1, 0);
			normalize(obj->co.axis);
		}
		cur = cur->next;
	}
}

void	translate_objects(t_mrt *m)
{
	t_list	*node;
	t_obj	*obj;
	mat4	mat;
	t_tup	n_pos;

	multi_tuple(n_pos, m->scene->camera.position, -1);
	translation_mat(mat, n_pos);
	translation_mat(m->inv.trsl, m->scene->camera.position);
	node = m->obj;
	while (node)
	{
		obj = node->content;
		if (obj->typ == SPHERE)
			multi_mat_tuple(obj->sp.pos, mat, obj->sp.pos);
		else if (obj->typ == PLANE)
			multi_mat_tuple(obj->pl.point, mat, obj->pl.point);
		else if (obj->typ == CONE)
			multi_mat_tuple(obj->co.apex, mat, obj->co.apex);
		else if (obj->typ == CYLINDER)
			multi_mat_tuple(obj->cy.pos, mat, obj->cy.pos);
		node = node->next;
	}
	multi_mat_tuple(m->scene->camera.position, mat, m->scene->camera.position);
}

void	adjust_lights_to_view(t_scene *scene, mat4 mat)
{
	t_list	*node;
	t_light	*light;
	t_tup	tmp;

	node = scene->lights_list;
	while (node)
	{
		light = node->content;
		multi_mat_tuple(tmp, mat, light->position);
		copy_tup(light->position, tmp);
		node = node->next;
	}
}

void	project_objects_subfcn(t_mrt *m, mat4 mat)
{
	t_list	*node;
	t_obj	*obj;
	t_tup	tup;

	node = m->obj;
	while (node)
	{
		obj = node->content;
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
		node = node->next;
	}
}

// project objects on to camera's axes. This is done so that the objects in the
// same direction as camera's orientation vector are now in front of the camera.
void	project_objects(t_mrt *m)
{
	mat4	mat;

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
	transpose_mat(*copy_mat(m->inv.proj, mat));
	multi_mat_mat(m->inv.final, m->inv.trsl, m->inv.proj);
	project_objects_subfcn(m, mat);
	adjust_lights_to_view(m->scene, mat);
	copy_vector(m->scene->camera.orientation_vector, (t_tup){0, 0, 1});
}
