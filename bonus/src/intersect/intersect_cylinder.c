/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 18:24:38 by vramacha          #+#    #+#             */
/*   Updated: 2026/01/31 15:20:48 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

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

double	proj_len(double t, t_cylinder *cy, t_ray *r)
{
	t_tup	l;

	multi_tuple(l, r->direction, t);
	add_tuples(l, r->origin, l);
	sub_tuples(l, l, cy->pos);
	return (fabs(dot_prod(l, cy->axis)));
}

static void	resolve_hitpoint(double *t, t_cylinder *cy, t_ray *r)
{
	if ((0 < t[0]) && ((cy->height / 2) < proj_len(t[0], cy, r)))
		t[0] = -INFINITY;
	if ((0 < t[1]) && ((cy->height / 2) < proj_len(t[1], cy, r)))
		t[1] = -INFINITY;
}

void	inter_cylinder(double *t, t_cylinder *cy, t_ray *r)
{
	t_tup	l;
	t_tup	p_v;
	t_tup	q_v;
	double	dlt;

	sub_tuples(l, r->origin, cy->pos);
	compute_pv(p_v, r->direction, cy->axis);
	compute_qv(q_v, cy, r);
	dlt = delta(dot_prod(p_v, p_v),
			dot_prod(p_v, q_v),
			dot_prod(q_v, q_v) - ((cy->dia * cy->dia) * 0.25));
	if (dlt < 0 || dot_prod(p_v, p_v) == 0)
	{
		t[0] = -INFINITY;
		t[1] = -INFINITY;
	}
	else
	{
		get_hitpoints(t, dot_prod(p_v, p_v), dot_prod(p_v, q_v), sqrt(dlt));
		resolve_hitpoint(t, cy, r);
	}
}
