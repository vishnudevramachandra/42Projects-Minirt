/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_rendering.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 16:31:36 by majkijew          #+#    #+#             */
/*   Updated: 2026/01/14 17:17:19 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_color(t_rgb *c)
{
	if (!c)
		return ;
	printf("Color: R=%.2d, G=%.2d, B=%.2d\n", c->r, c->g, c->b);
}

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

int	is_in_shadow(t_mrt *m, t_inter *hit, t_tup light_unit_vec)
{
	t_ray	shadow_ray;
	double	light_dist;
	t_list	*cur;
	t_obj	*obj;
	double	t;

	sub_tuples(light_unit_vec, m->scene->light.position, hit->hit_point);
	light_dist = magnitude(light_unit_vec);
	normalize(light_unit_vec);
	cur = m->obj;
	while (cur)
	{
		obj = cur->content;
		t = -1;
		if (obj->typ == SPHERE)
			t = inter_sphere(obj->sp, shadow_ray);
		else if (obj->typ == PLANE)
			t = inter_plane(&obj->pl, &shadow_ray);
		// else if (obj->typ == CYLINDER)
		//	 t = inter_cylinder(obj->cy, shadow_ray);
		if (t > EPSILON && t < light_dist)
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

void	add_direct_component(t_rgb *final_col, t_rgb *obj_col, t_mrt *m,
	double cos_theta)
{
	t_rgb	direct_illumination;
	t_rgb	direct_color;

	mult_scalar_colors(&direct_illumination, &m->scene->light.color,
		cos_theta * m->scene->light.bright_ratio);
	multi_colors(&direct_color, obj_col, &direct_illumination);
	add_colors(final_col, final_col, &direct_color);
}

void	add_specular_component(t_rgb *final_col, t_mrt *m, t_inter *i,
	t_tup light_unit_vec)
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
	mult_scalar_colors(&spec_color, &m->scene->light.color,
		pow(cos_theta, i->obj->sp.mt.shininess) * m->scene->light.bright_ratio);
	add_colors(final_col, final_col, &spec_color);
}

void	final_obj_light(t_rgb *final_col, t_mrt *m, t_inter *i)
{
	t_rgb	*obj_col;
	t_tup	light_unit_vec;
	double	cos_theta;

	find_obj_color(&obj_col, m, i);
	add_ambient_component(final_col, obj_col, m);
	if (is_in_shadow(m, i, light_unit_vec))
	{
		// color_range(final_col);
		// return ;
	}
	cos_theta = dot_prod(i->normal, light_unit_vec);
	if (cos_theta <= 0)
	{
		color_range(final_col);
		return ;
	}
	add_direct_component(final_col, obj_col, m, cos_theta);
	add_specular_component(final_col, m, i, light_unit_vec);
	color_range(final_col);
}

void	render_obj(t_mrt *m, t_inter *i, int x, int y)
{
	t_tup	scaled;
	t_rgb	final_color;

	multi_tuple(scaled, m->ray.direction, i->t);
	add_tuples(i->hit_point, m->ray.origin, scaled);
	normal_at(i->normal, i->obj, i->hit_point);
	final_obj_light(&final_color, m, i);
	mlx_put_pixel(m->image, x, y, get_rgba(&final_color, 1));
}

void	insert_intersection(t_inter **list, t_inter *new, t_obj *obj, double t)
{
	t_inter	*cur;

	if (!new)
	{
		//has to be handled;
	}
	new->t = t;
	new->obj = obj;
	if (*list == NULL || new->t < (*list)->t)
	{
		new->next = *list;
		*list = new;
		return ;
	}
	cur = *list;
	while (cur->next && cur->next->t < new->t)
		cur = cur->next;
	new->next = cur->next;
	cur->next = new;
}

void	free_list(t_inter *i)
{
	t_inter	*temp;

	while (i)
	{
		temp = i->next;
		free(i);
		i = temp;
	}
}

// those vectors that are supposed to be normal vectors are normalized
void	normalize_vectors(t_mrt *m)
{
	t_list	*cur;
	t_obj	*obj;
	t_tup	vec;

	normalize(m->scene->camera.orientation_vector);
	if (!m->obj)
		return ;
	cur = m->obj;
	while (cur)
	{
		obj = cur->content;
		if (obj->typ == PLANE)
		{
			normalize(obj->pl.norm_vec);
			if (0 < dot_prod(*perpvec_to_plane(vec, &obj->pl), obj->pl.norm_vec))
				multi_tuple(obj->pl.norm_vec, obj->pl.norm_vec, -1);
		}
		cur = cur->next;
	}
}

void	compute_intersections(t_inter **inter, t_mrt *m)
{
	t_list	*current;
	t_obj	*obj;
	double	t;

	current = m->obj;
	while (current)
	{
		obj = current->content;
		t = -1;
		if (obj->typ == SPHERE)
			t = inter_sphere(obj->sp, m->ray);
		else if (obj->typ == PLANE)
			t = inter_plane(&obj->pl, &m->ray);
		// if (obj->typ == CYLINDER)
		// 	t = inter_cylinder(obj->sp, m->ray);
		if (0 < t)
			insert_intersection(inter, malloc(sizeof(t_inter)), obj, t);
		current = current->next;
	}
}

void	canvas(t_mrt *m)
{
	uint32_t	x;
	uint32_t	y;
	t_view		view;
	t_inter		*inter;

	normalize_vectors(m);
	translate_objects(m);
	project_objects(m);
	setup_viewport(&view, m);
	y = 0;
	while (y < m->image->height)
	{
		x = 0;
		while (x < m->image->width)
		{
			calc_direction(&m->scene->camera, &view, x, y);
			create_ray(&m->ray, m->scene->camera.position,
				m->scene->camera.orientation_vector);
			inter = NULL;
			compute_intersections(&inter, m);
			if (inter)
			{	
				render_obj(m, inter, x, y);
				free_list(inter);
			}
			x++;
		}
		y++;
	}
}
