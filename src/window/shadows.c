/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 18:19:12 by vramacha          #+#    #+#             */
/*   Updated: 2026/01/27 16:51:58 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minirt.h"

static void	create_shadow_ray(t_ray *shadow_ray, t_inter *hit,
	t_tup light_unit_vec)
{
	t_tup	offset;

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

double	inter_obj(t_obj *obj, t_ray *ray)
{
	double	t;

	t = -1;
	if (obj->typ == SPHERE)
		t = inter_sphere(&obj->sp, ray);
	else if (obj->typ == PLANE)
		t = inter_plane(&obj->pl, ray);
	else if (obj->typ == CYLINDER)
		t = inter_cylinder(&obj->cy, ray);
	else if (obj->typ == CONE)
		t = inter_cone(&obj->co, ray);
	return (t);
}

int	is_in_shadow(t_mrt *m, t_inter *hit, t_tup light_unit_vec, t_light *light)
{
	t_ray	shadow_ray;
	double	light_dist;
	t_list	*cur;
	t_obj	*obj;
	double	t;

	compute_light_unit_vec(light_unit_vec, &light_dist, light, hit);
	create_shadow_ray(&shadow_ray, hit, light_unit_vec);
	cur = m->obj;
	while (cur)
	{
		obj = cur->content;
		t = inter_obj(obj, &shadow_ray);
		if (EPSILON < t && t < light_dist)
			return (1);
		cur = cur->next;
	}
	return (0);
}
