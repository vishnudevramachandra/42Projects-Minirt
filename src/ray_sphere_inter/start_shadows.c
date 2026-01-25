/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shadows.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:59:40 by majkijew          #+#    #+#             */
/*   Updated: 2026/01/25 13:52:20 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	normalize_cone(t_tup normal, t_tup point)
{
	double	y;

	y = sqrt(point[0] * point[0] + point[2] * point[2]);
	if (point[1] > 0)
		y = -y;
	init_vector(normal, point[0], y, point[2]);
	normalize(normal);
}

void	normal_at(t_tup normal, t_obj *obj, t_tup point)
{
	if (obj->typ == SPHERE)
	{
		sub_tuples(normal, point, obj->sp.pos);
		normalize(normal);
	}
	else if (obj->typ == PLANE)
		copy_tup(normal, obj->pl.norm_vec);
	else if (obj->typ == CONE)
		normalize_cone(normal, point);
}

void	reflect(t_tup out, t_tup in, t_tup normal)
{
	t_tup	normal_comp_ray;

	multi_tuple(normal_comp_ray, normal, 2 * dot_prod(in, normal));
	sub_tuples(out, in, normal_comp_ray);
}
