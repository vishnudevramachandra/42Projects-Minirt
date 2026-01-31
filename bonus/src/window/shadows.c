/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 18:19:12 by vramacha          #+#    #+#             */
/*   Updated: 2026/02/01 00:26:25 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	invert_normal_if_inside_cy(t_inter *hit)
{
	if (0 <= hit->t0)
		return ;
	multi_tuple(hit->normal, hit->normal, -1);
}

static void	create_shadow_ray(t_ray *shadow_ray, t_inter *hit,
	t_tup light_unit_vec)
{
	t_tup	offset;

	if (hit->obj->typ == CYLINDER)
		invert_normal_if_inside_cy(hit);
	multi_tuple(offset, light_unit_vec, EPSILON);
	add_tuples(shadow_ray->origin, hit->hit_point, offset);
	copy_tup(shadow_ray->direction, light_unit_vec);
}

void	compute_light_unit_vec(t_tup light_unit_vec, double *light_dist,
	t_light *light, t_inter *hit)
{
	sub_tuples(light_unit_vec, light->position, hit->hit_point);
	*light_dist = magnitude(light_unit_vec);
	normalize(light_unit_vec);
}

int	is_in_shadow(t_mrt *m, t_inter *hit, t_tup light_unit_vec,
		double light_dist)
{
	t_ray	shadow_ray;
	t_list	*cur;
	t_obj	*obj;
	double	t[2];

	create_shadow_ray(&shadow_ray, hit, light_unit_vec);
	cur = m->obj;
	while (cur)
	{
		if (obj == hit->obj)
		{
			cur = cur->next;
			continue ;
		}
		obj = cur->content;
		inter_obj(t, obj, &shadow_ray);
		if ((t[0] > EPSILON && t[0] < light_dist)
			|| (t[1] > EPSILON && t[1] < light_dist))
			return (1);
		cur = cur->next;
	}
	return (0);
}
