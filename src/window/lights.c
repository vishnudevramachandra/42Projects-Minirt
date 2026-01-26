/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 17:33:04 by majkijew          #+#    #+#             */
/*   Updated: 2026/01/26 19:31:34 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	color_range(t_rgb *c)
{
	if (c->r > 255)
		c->r = 255;
	if (c->g > 255)
		c->g = 255;
	if (c->b > 255)
		c->b = 255;
}

void	find_obj_color(t_rgb **obj_col, t_mrt *m, t_inter *i)
{
	t_tup	inv_hit_point;

	if (!i->obj->sp.mt.pattern.fcn)
		*obj_col = &i->obj->sp.mt.pattern.color1;
	else
	{
		multi_mat_tuple(inv_hit_point, m->inv.final, i->hit_point);
		*obj_col = i->obj->sp.mt.pattern.fcn(
				i->obj->sp.mt.pattern.param,
				&i->obj->sp.mt.pattern.color1,
				&i->obj->sp.mt.pattern.color2,
				inv_hit_point);
	}
}

void	create_shadow_ray(t_ray *shadow_ray, t_inter *hit, t_tup light_unit_vec)
{
	t_tup	offset;

	multi_tuple(offset, hit->normal, EPSILON);
	add_tuples(shadow_ray->origin, hit->hit_point, offset);
	copy_tup(shadow_ray->direction, light_unit_vec);
}

int	is_in_shadow(t_mrt *m, t_inter *hit, t_tup light_unit_vec, t_light *light)
{
	t_ray	shadow_ray;
	double	light_dist;
	t_list	*cur;
	t_obj	*obj;
	double	t;

	sub_tuples(light_unit_vec, light->position, hit->hit_point);
	light_dist = magnitude(light_unit_vec);
	normalize(light_unit_vec);
	create_shadow_ray(&shadow_ray, hit, light_unit_vec);
	cur = m->obj;
	while (cur)
	{
		obj = cur->content;
		t = -1;
		if (obj->typ == SPHERE)
			t = inter_sphere(&obj->sp, &shadow_ray);
		else if (obj->typ == PLANE)
			t = inter_plane(&obj->pl, &shadow_ray);
		else if (obj->typ == CYLINDER)
			t = inter_cylinder(&obj->cy, &shadow_ray);
		else if (obj->typ == CONE)
			t = inter_cone(obj->co, shadow_ray);
		if (EPSILON < t && t < light_dist)
			return (1);
		cur = cur->next;
	}
	return (0);
}

void	add_ambient_component(t_rgb *final_col, t_rgb *obj_col, t_mrt *m)
{
	t_rgb	ambient_illumination;

	mult_scalar_colors(&ambient_illumination, &m->scene->amb_light.color,
		m->scene->amb_light.ratio);
	multi_colors(final_col, obj_col, &ambient_illumination);
}

void	add_direct_component(t_rgb *final_col, t_rgb *obj_col, t_light *light,
	double cos_theta)
{
	t_rgb	direct_illumination;
	t_rgb	direct_color;

	mult_scalar_colors(&direct_illumination, &light->color,
		cos_theta * light->bright_ratio);
	multi_colors(&direct_color, obj_col, &direct_illumination);
	add_colors(final_col, final_col, &direct_color);
}

void	add_specular_component(t_rgb *final_col, t_mrt *m, t_inter *i,
	t_tup light_unit_vec, t_light *light)
{
	t_tup	view_unit_vec;
	t_tup	neg_vec;
	t_tup	reflected_light_vec;
	double	cos_theta;
	t_rgb	spec_color;

	sub_tuples(view_unit_vec, m->scene->camera.position, i->hit_point);
	normalize(view_unit_vec);
	multi_tuple(neg_vec, light_unit_vec, -1);
	reflect(reflected_light_vec, neg_vec, i->normal);
	cos_theta = dot_prod(reflected_light_vec, view_unit_vec);
	if (cos_theta <= 0)
		return ;
	mult_scalar_colors(&spec_color, &light->color,
		pow(cos_theta, i->obj->sp.mt.shininess) * light->bright_ratio);
	add_colors(final_col, final_col, &spec_color);
}

void	final_obj_light(t_rgb *final_col, t_mrt *m, t_inter *i)
{
	t_rgb	*obj_col;
	t_tup	light_unit_vec;
	double	cos_theta;
	t_list	*node;
	t_light	*light;

	node = m->scene->lights_list;
	find_obj_color(&obj_col, m, i);
	add_ambient_component(final_col, obj_col, m);
	while (node)
	{
		light = node->content;
		if (is_in_shadow(m, i, light_unit_vec, light))
		{
			node = node->next;
			continue ;
		}
		cos_theta = dot_prod(i->normal, light_unit_vec);
		if (cos_theta <= 0)
		{
			node = node->next;
			continue ;
		}
		add_direct_component(final_col, obj_col, light, cos_theta);
		add_specular_component(final_col, m, i, light_unit_vec, light);
		node = node->next;
	}
	color_range(final_col);
}
