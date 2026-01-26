/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 18:02:23 by vramacha          #+#    #+#             */
/*   Updated: 2026/01/26 18:03:31 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minirt.h"

double	inter_cone(t_cone co, t_ray r)
{
	double	t[2];
	double	k;
	t_tup	l;
	double	a;
	double	b_half;
	double	c;
	double	dlt;

	k = (co.dia * 0.5) / co.height;
	sub_tuples(l, r.origin, co.pos);
	a = r.direction[0] * r.direction[0] + r.direction[2]
		* r.direction[2] - k * k * r.direction[1] * r.direction[1];
	if (fabs(a) < EPSILON)
		return (-1);
	b_half = l[0] * r.direction[0] + l[2] * r.direction[2]
		- k * k * l[1] * r.direction[1];
	c = l[0] * l[0] + l[2] * l[2] - k * k * l[1] * l[1];
	dlt = delta(a, b_half, c);
	if (dlt < 0)
		return (-1);
	else
	{
		get_hitpoints(t, a, b_half, sqrt(dlt));
		if (t[1] < 0)
			return (-1);
		if (0 < t[0])
			return (t[0]);
		else
			return (t[1]);
	}
}
