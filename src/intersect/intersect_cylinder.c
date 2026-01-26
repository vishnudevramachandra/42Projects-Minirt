/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 18:24:38 by vramacha          #+#    #+#             */
/*   Updated: 2026/01/26 14:57:18 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minirt.h"

static void	compute_pv(t_tup p_v, t_tup dir, t_tup axis)
{
	double	dot_dir_axis;
	t_tup	tmp;

	dot_dir_axis = dot_prod(dir, axis);
	multi_tuple(tmp, axis, dot_dir_axis);
	sub_tuples(p_v, tmp, dir);
}

static void	compute_qv(t_tup q_v, t_cylinder *cy, t_ray *r)
{
	t_tup	l;

	sub_tuples(l, r->origin, cy->pos);
	compute_pv(q_v, l, cy->axis);
}

double	inter_cylinder(t_cylinder *cy, t_ray *r)
{
	t_tup	l;
	t_tup	p_v;
	t_tup	q_v;
	double	dlt;
	double	t;

	sub_tuples(l, r->origin, cy->pos);
	compute_pv(p_v, r->direction, cy->axis);
	compute_qv(q_v, cy, r);
	dlt = delta(dot_prod(p_v, p_v),
			dot_prod(p_v, q_v),
			dot_prod(q_v, q_v) - ((cy->dia * cy->dia) * 0.25));
	if (dlt < 0)
		return (-1);
	else if (dot_prod(p_v, p_v) == 0)
		return (-1);
	else
	{
		// t = get_hitpoint(dot_prod(p_v, p_v), dot_prod(p_v, q_v), sqrt(dlt));
		t = -1;
		if (t != -1)
		{
			multi_tuple(l, r->direction, t);
			add_tuples(l, r->origin, l);
			sub_tuples(l, l, cy->pos);
			if ((cy->height / 2) < fabs(dot_prod(l, cy->axis)))
				t = -1;
		}
	}
	return (t);
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
