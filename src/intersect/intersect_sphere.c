/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 18:22:47 by vramacha          #+#    #+#             */
/*   Updated: 2026/01/26 15:48:22 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minirt.h"

// l is the vector that points from sphere center to ray origin
// t = ( (2 * b_h) +/- sqrt((2 * b_h) * (2 * b_h) - (4 * a * c)) ) / (2 * a) can
// be converted to t = (b_h +/- sqrt((b_h * b_h) - (a * c))) / a
// TODO: if we always normalize the ray.direction then we can replace a = 1.
double	inter_sphere(t_sphere *sp, t_ray *r)
{
	t_tup	l;
	double	dlt;
	double	t[2];

	sub_tuples(l, r->origin, sp->pos);
	dlt = delta(dot_prod(r->direction, r->direction),
			dot_prod(r->direction, l),
			dot_prod(l, l) - ((sp->dia * sp->dia) * 0.25));
	if (dlt < 0)
		return (-1);
	else
	{
		get_hitpoints(t,
			dot_prod(r->direction, r->direction),
			dot_prod(r->direction, l),
			sqrt(dlt));
		if (t[1] < 0)
			return (-1);
		if (0 < t[0])
			return (t[0]);
		else
			return (t[1]);
	}
}
