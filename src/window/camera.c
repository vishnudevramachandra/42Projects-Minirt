/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 19:48:39 by majkijew          #+#    #+#             */
/*   Updated: 2025/12/15 13:21:16 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minirt.h"

// camera orientation vector is computed step-by-step to cover the field of view
void	calc_direction(t_camera *cam, t_view *view, int x, int y)
{
	t_tup	point;

	init_point(point,
		view->h_start_pos + (x * view->px_width),
		view->v_start_pos - (y * view->px_width),
		1);
	sub_tuples(cam->orientation_vector, point, cam->position);
	normalize(cam->orientation_vector);
}

// sets up the viewport parameters based on camera and image properties
void	setup_viewport(t_view *view, t_mrt *m)
{
	double	half_h_dist;
	
	half_h_dist = tan((m->scene->camera.horizontal_field / 180 * M_PI) / 2);
	view->px_width = (half_h_dist * 2) / m->image->width;
	view->h_start_pos = -half_h_dist + (view->px_width / 2);
	view->v_start_pos = half_h_dist\
		* ((double)m->image->height / m->image->width) - (view->px_width / 2);
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
		else if (obj->typ == PLANE)
			multi_mat_tuple(obj->pl.point, mat, obj->pl.point);
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
			copy_tup(obj->sp.pos, tup);
		}
		else if (obj->typ == PLANE)
		{
			multi_mat_tuple(tup, mat, obj->pl.point);
			copy_tup(obj->pl.point, tup);
			multi_mat_tuple(tup, mat, obj->pl.norm_vec);
			copy_tup(obj->pl.norm_vec, tup);
		}
		node = node->next;
	}
	multi_mat_tuple(m->scene->light.position, mat, m->scene->light.position);
	copy_vector(m->scene->camera.orientation_vector, (t_tup){0, 0, 1});
}