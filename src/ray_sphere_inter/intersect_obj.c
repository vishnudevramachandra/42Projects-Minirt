/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 22:06:26 by majkijew          #+#    #+#             */
/*   Updated: 2025/11/24 20:58:19 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	delta(double a, double b, double c)
{
	return (b * b - 4 * a * c);
}

double	get_hitpoint( double a, double b, double sqrt_dlt)
{
	double	t;
	double	t1;
	double	t2;

	t1 = ((-b - sqrt_dlt) / (a * 2));
	t2 = ((-b + sqrt_dlt) / (a * 2));

	if (t1 > 0 && t2 > 0)
	{
		if (t1 > t2)
			t = t2;
		else
			t = t1;
	}
	else if (t1 > 0)
		t = t1;
	else if (t2 > 0)
		t = t2;
	else
		t = -1;
	return (t);
}

double	inter_sphere(t_sphere sp, t_ray r)
{
	t_tup	l;
	double	dlt;
	double	t;

	init_vector(l, 0, 0, 0);
	sub_tuples(l, r.origin, sp.pos);
	dlt = delta(dot_prod(r.direction, r.direction),
			2 * dot_prod(r.direction, l), dot_prod(l, l)
			- ((sp.dia * sp.dia) * 0.5));
	if (dlt < 0)
		return (-1);
	else if (dlt == 0)
	{
		t = -(2 * dot_prod(r.direction, l))
			/ (dot_prod(r.direction, r.direction)) * 2;
		if (t < 0)
			return (-1);
		return (t);
	}
	else
	{
		t = get_hitpoint(dot_prod(r.direction, r.direction),
				2 * dot_prod(r.direction, l), sqrt(dlt));
	}
	return (t);
}
