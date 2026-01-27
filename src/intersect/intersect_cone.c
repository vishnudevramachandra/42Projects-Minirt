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

static double	resolve_hitpoint(double *t, t_cone *co, t_ray *r)
{
	double	y;

	if (t[0] > EPSILON)
	{
		y = proj_len(t[0], co, r);
		if (y >= 0 && y <= co->height)
			return (t[0]);
	}
	if (t[1] > EPSILON)
	{
		y = proj_len(t[1], co, r);
		if (y >= 0 && y <= co->height)
			return (t[1]);
	}
	return (-1);
}

// c = l[0] * l[0] + l[2] * l[2] - k * l[1] * l[1]
double	inter_cone(t_cone *co, t_ray *r)
{
	double	t[2];
	double	k;
	t_tup	l;
	double	a;
	double	b_half;

	k = (co->dia * 0.5) / co->height * (co->dia * 0.5) / co->height;
	sub_tuples(l, r->origin, co->apex);
	a = r->direction[0] * r->direction[0] + r->direction[2] * r->direction[2]
		- k * r->direction[1] * r->direction[1];
	if (fabs(a) < EPSILON)
		return (-1);
	b_half = l[0] * r->direction[0] + l[2] * r->direction[2]
		- k * l[1] * r->direction[1];
	if (delta(a, b_half, l[0] * l[0] + l[2] * l[2] - k * l[1] * l[1]) < 0)
		return (-1);
	get_hitpoints(t, a, b_half, sqrt(delta(a, b_half,
				l[0] * l[0] + l[2] * l[2] - k * l[1] * l[1])));
	return (resolve_hitpoint(t, co, r));  
}
