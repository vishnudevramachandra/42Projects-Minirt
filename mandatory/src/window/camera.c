/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 19:48:39 by majkijew          #+#    #+#             */
/*   Updated: 2026/01/26 21:11:42 by vramacha         ###   ########.fr       */
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
	view->v_start_pos = half_h_dist \
	* ((double)m->image->height / m->image->width) - (view->px_width / 2);
}
