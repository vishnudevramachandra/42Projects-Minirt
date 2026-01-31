/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shadows.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:59:40 by majkijew          #+#    #+#             */
/*   Updated: 2026/01/31 00:05:37 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	normalize_cone(t_tup normal, t_cone *co, t_tup hit_point)
{
	t_tup	p;
	double	k;

	sub_tuples(p, hit_point, co->apex);
	k = (co->dia / 2) / co->height;
	init_vector(normal, p[0], -(k * k) * p[1], p[2]);
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
		normalize_cone(normal, &obj->co, hit_point);
	else if (obj->typ == CYLINDER)
		compute_cy_normal(normal, hit_point, &obj->cy);
	else if (obj->typ == TEXTURE)
		normal_at(normal, obj->tx.sub_obj, hit_point);
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
