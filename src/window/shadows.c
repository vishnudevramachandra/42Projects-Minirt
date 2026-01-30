/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 18:19:12 by vramacha          #+#    #+#             */
/*   Updated: 2026/01/28 23:09:06 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minirt.h"

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
	multi_tuple(offset, hit->normal, EPSILON);
	add_tuples(shadow_ray->origin, hit->hit_point, offset);
	copy_tup(shadow_ray->direction, light_unit_vec);
}

static void	compute_light_unit_vec(t_tup light_unit_vec, double *light_dist,
	t_light *light, t_inter *hit)
{
	sub_tuples(light_unit_vec, light->position, hit->hit_point);
	*light_dist = magnitude(light_unit_vec);
	normalize(light_unit_vec);
}

int	is_in_shadow(t_mrt *m, t_inter *hit, t_tup light_unit_vec, t_light *light)
{
	t_ray	shadow_ray;
	double	light_dist;
	t_list	*cur;
	t_obj	*obj;
	double	t[2];

	compute_light_unit_vec(light_unit_vec, &light_dist, light, hit);
	create_shadow_ray(&shadow_ray, hit, light_unit_vec);
	cur = m->obj;
	while (cur)
	{
		obj = cur->content;
		inter_obj(t, obj, &shadow_ray);
		if (EPSILON < t[0] && t[0] < light_dist)
			return (1);
		else if (EPSILON < t[1] && t[1] < light_dist)
			return (1);
		cur = cur->next;
	}
	return (0);
}
