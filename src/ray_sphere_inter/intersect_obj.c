/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 22:06:26 by majkijew          #+#    #+#             */
/*   Updated: 2026/01/14 13:27:54 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minirt.h"

double	delta(double a, double b_h, double c)
{
	return ((b_h * b_h) - (a * c));
}

double	get_hitpoint(double a, double b_h, double sqrt_dlt)
{
	double	t;
	double	t1;
	double	t2;

	t1 = (-b_h - sqrt_dlt) / a;
	t2 = (-b_h + sqrt_dlt) / a;
	if (t1 > 0 || t2 > 0)
	{
		if (t1 > t2)
			t = t2;
		else
			t = t1;
	}
	else
		t = -1;
	return (t);
}

// l is the vector that points from sphere center to ray origin
// t = ( (2 * b_h) +/- sqrt((2 * b_h) * (2 * b_h) - (4 * a * c)) ) / (2 * a) can
// be converted to t = (b_h +/- sqrt((b_h * b_h) - (a * c))) / a
// TODO: if we always normalize the ray.direction then we can replace a = 1.
double	inter_sphere(t_sphere sp, t_ray r)
{
	t_tup	l;
	double	dlt;
	double	t;

	sub_tuples(l, r.origin, sp.pos);
	dlt = delta(dot_prod(r.direction, r.direction),
			dot_prod(r.direction, l),
			dot_prod(l, l) - ((sp.dia * sp.dia) * 0.25));
	if (dlt < 0)
		return (-1);
	else
		t = get_hitpoint(dot_prod(r.direction, r.direction),
				dot_prod(r.direction, l),
				sqrt(dlt));
	return (t);
}

// compute the perpendicular vector from the origin to the plane
t_tup	*perpvec_to_plane(t_tup vec, t_plane *pl)
{
	double	m;

	sub_tuples(vec, pl->point, (double[4]){0, 0, 0, 1});
	m = dot_prod(pl->norm_vec, vec);
	multi_tuple(vec, pl->norm_vec, m);
	return ((t_tup *)vec);
}

double	inter_plane(t_plane *pl, t_ray *r)
{
	t_tup	perp_vec;

	if (fabs(dot_prod(pl->norm_vec, r->direction)) < __DBL_EPSILON__)
		return (-INFINITY);
	perpvec_to_plane(perp_vec, pl);
	return (dot_prod(perp_vec, perp_vec) / dot_prod(r->direction, perp_vec));
}
