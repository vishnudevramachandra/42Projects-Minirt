/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 22:06:26 by majkijew          #+#    #+#             */
/*   Updated: 2025/11/19 22:46:38 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	delta(double a, double b, double c)
{
	return (b * b - 4 * a * c);
}

void	inter_sphere(t_sphere sp, t_ray r)
{
	t_tup	l;
	double	dlt;
	double	t;
	double	t1;
	double	t2;

	init_vector(l, 0, 0, 0);
	sub_tuples(l, r.origin, sp.pos);
	dlt = delta(1, 2 * dot_prod(r.direction, l), dot(l, l) - sqrt(sp.dia));
	if (delta < 0)
		return ;
	
}
