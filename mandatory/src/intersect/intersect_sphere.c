/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 18:22:47 by vramacha          #+#    #+#             */
/*   Updated: 2026/01/31 02:09:18 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minirt.h"

// l is the vector that points from sphere center to ray origin
// t = ( (2 * b_h) +/- sqrt((2 * b_h) * (2 * b_h) - (4 * a * c)) ) / (2 * a) can
// be converted to t = (b_h +/- sqrt((b_h * b_h) - (a * c))) / a
void	inter_sphere(double *t, t_sphere *sp, t_ray *r)
{
	t_tup	l;
	double	dlt;

	sub_tuples(l, r->origin, sp->pos);
	dlt = delta(dot_prod(r->direction, r->direction),
			dot_prod(r->direction, l),
			dot_prod(l, l) - ((sp->dia * sp->dia) * 0.25));
	if (dlt < 0)
	{
		t[0] = -INFINITY;
		t[1] = -INFINITY;
	}
	else
	{
		get_hitpoints(t,
			dot_prod(r->direction, r->direction),
			dot_prod(r->direction, l),
			sqrt(dlt));
	}
}
