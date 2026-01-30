/* ************************************************************************** */
/*			                                                                */
/*                                                        :::      ::::::::   */
/*   intersect_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 18:02:23 by vramacha          #+#    #+#             */
/*   Updated: 2026/01/27 13:57:13 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	proj_len(double t, t_cone *co, t_ray *r)
{
	t_tup	p;

	multi_tuple(p, r->direction, t);
	add_tuples(p, r->origin, p);
	return (co->apex[1] - p[1]);
}

static void	resolve_hitpoint(double *t, t_cone *co, t_ray *r)
{
	double	y;

	if (EPSILON < t[0])
	{
		y = proj_len(t[0], co, r);
		if (y < 0 && co->height < y)
			t[0] = -INFINITY;
	}
	if (EPSILON < t[1])
	{
		y = proj_len(t[1], co, r);
		if (y < 0 && co->height < y)
			t[1] = -INFINITY;
	}
}

// c = l[0] * l[0] + l[2] * l[2] - k * l[1] * l[1]
void	inter_cone(double *t, t_cone *co, t_ray *r)
{
	double	k;
	t_tup	l;
	double	a;
	double	b_half;
	double	dlt;

	k = (co->dia * 0.5) / co->height * (co->dia * 0.5) / co->height;
	sub_tuples(l, r->origin, co->apex);
	a = r->direction[0] * r->direction[0] + r->direction[2] * r->direction[2]
		- k * r->direction[1] * r->direction[1];
	b_half = l[0] * r->direction[0] + l[2] * r->direction[2]
		- k * l[1] * r->direction[1];
	dlt = delta(a, b_half, l[0] * l[0] + l[2] * l[2] - k * l[1] * l[1]);
	if (fabs(a) < EPSILON || dlt < 0)
	{
		t[0] = -INFINITY;
		t[1] = -INFINITY;
	}
	else
	{
		get_hitpoints(t, a, b_half, sqrt(dlt));
		resolve_hitpoint(t, co, r);
	}
}
