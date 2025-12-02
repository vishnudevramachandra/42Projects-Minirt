/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 22:06:26 by majkijew          #+#    #+#             */
/*   Updated: 2025/12/02 16:20:13 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
// t = ( (2 * b_h) +/- sqrt((2 * b_h) * (2 * b_h) - (4 * a * c)) ) / (2 * a) can be
// converted to t = (b_h +/- sqrt((b_h * b_h) - (a * c))) / a
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
