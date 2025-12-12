/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 19:48:39 by majkijew          #+#    #+#             */
/*   Updated: 2025/12/10 14:59:23 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// camera orientation vector is rotated step-by-step to cover the field of view
void	calc_direction(t_tup dir, t_tup ori_vec, double pitch, double roll)
{
	mat4	m;

	// Create rotation matrix
	rotation_mat(m, (double [3]){0, pitch, roll});
	// Apply combined rotation to the original orientation vector
	multi_mat_tuple(dir, m, ori_vec);
}

// sets up the viewport parameters based on camera and image properties
void	setup_viewport(t_view *view, t_mrt *m)
{
	double	h_field_in_radians;
	double	v_field_in_radians;

	h_field_in_radians = m->scene->camera.horizontal_field / 180 * M_PI;
	view->pitch_start = h_field_in_radians / 2;
	view->pitch_delta= h_field_in_radians / (m->image->width - 1);
	v_field_in_radians = (double)m->image->height / m->image->width\
					* h_field_in_radians;
	view->roll_start = v_field_in_radians / 2;
	view->roll_delta= v_field_in_radians / (m->image->height - 1);
}

// translates objects using negative of camera's position, effectively
// recentering the co-ordinate system so that the camera resides at the origin.
void	translate_objects(t_mrt *m)
{
	t_list	*node;
	t_obj	*obj;
	mat4	mat;
	t_tup	n_pos;

	multi_tuple(n_pos, m->scene->camera.position, -1);
	translation_mat(mat, n_pos);
	node = m->obj;
	while (node)
	{
		obj = node->content;
		if (obj->typ == SPHERE)
			multi_mat_tuple(obj->sp.pos, mat, obj->sp.pos);
		node = node->next;
	}
	multi_mat_tuple(m->scene->light.position, mat, m->scene->light.position);
	multi_mat_tuple(m->scene->camera.position, mat, m->scene->camera.position);
}

// project objects on to camera's axes. This is done so that the objects in the
// same direction as camera's orientation vector are now in front of the camera.
void	project_objects(t_mrt *m)
{
	mat4	mat;
	t_list	*node;
	t_obj	*obj;
	t_tup	tup;

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
	node = m->obj;
	while (node)
	{
		obj = node->content;
		if (obj->typ == SPHERE)
		{
			multi_mat_tuple(tup, mat, obj->sp.pos);
			copy_vector(obj->sp.pos, tup);
		}
		node = node->next;
	}
	multi_mat_tuple(m->scene->light.position, mat, m->scene->light.position);
	copy_vector(m->scene->camera.orientation_vector, (t_tup){0, 0, 1});
}