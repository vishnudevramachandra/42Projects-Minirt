/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shadows.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:59:40 by majkijew          #+#    #+#             */
/*   Updated: 2026/01/26 18:05:49 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	normalize_cone(t_tup normal, t_tup point)
{
	double	y;

	y = sqrt(point[0] * point[0] + point[2] * point[2]);
	if (point[1] > 0)
		y = -y;
	init_vector(normal, point[0], y, point[2]);
	normalize(normal);
}

void	normal_at(t_tup normal, t_obj *obj, t_tup hit_point)
{
	if (obj->typ == SPHERE)
	{
		sub_tuples(normal, hit_point, obj->sp.pos);
		normalize(normal);
	}
	else if (obj->typ == PLANE)
		copy_tup(normal, obj->pl.norm_vec);
	else if (obj->typ == CONE)
		normalize_cone(normal, hit_point);
	else if (obj->typ == CYLINDER)
		compute_cy_normal(normal, hit_point, &obj->cy);
}

void	reflect(t_tup out, t_tup in, t_tup normal)
{
	t_tup	normal_comp_ray;

	multi_tuple(normal_comp_ray, normal, 2 * dot_prod(in, normal));
	sub_tuples(out, in, normal_comp_ray);
}

void	project_point_on_vector(t_tup res, t_tup center_to_hit, t_tup vec)
{
	double	proj_len;

	proj_len = dot_prod(center_to_hit, vec);
	multi_tuple(res, vec, proj_len);
}

void	compute_cy_normal(t_tup normal, t_tup hit_point, t_cylinder *cy)
{
	t_tup	center_to_hit;
	t_tup	proj_on_axis;

	sub_tuples(center_to_hit, hit_point, cy->pos);
	project_point_on_vector(proj_on_axis, center_to_hit, cy->axis);
	sub_tuples(normal, center_to_hit, proj_on_axis);
	normalize(normal);
}
