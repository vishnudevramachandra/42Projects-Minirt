/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_rendering.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 16:31:36 by majkijew          #+#    #+#             */
/*   Updated: 2025/12/15 17:59:56 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_obj_color(t_rgb **obj_col, t_inter *i)
{
	if (i->obj->typ == SPHERE)
		*obj_col = &i->obj->sp.color;
	else if (i->obj->typ == PLANE)
		*obj_col = &i->obj->pl.color;
	else
		*obj_col = &i->obj->cy.color;
}
int is_in_shadow(t_mrt *m, t_inter *hit)
{
	t_ray	shadow_ray;
	t_tup	light_vec;
	t_tup	offset;
	double	light_dist;

	sub_tuples(light_vec,
		m->scene->light.position,
		hit->hit_point);
	light_dist = magnitude(light_vec);
	normalize(light_vec);
	multi_tuple(offset, hit->normal, EPSILON);
	add_tuples(shadow_ray.origin, hit->hit_point, offset);
	copy_tup(shadow_ray.direction, light_vec);
	t_list *cur = m->obj;
	while (cur)
	{
		t_obj *obj = cur->content;
		double t = -1;
		if (obj->typ == SPHERE)
			t = inter_sphere(obj->sp, shadow_ray);
		else if (obj->typ == PLANE)
			t = inter_plane(obj->pl, shadow_ray);
		// else if (obj->typ == CYLINDER)
		//	 t = inter_cylinder(obj->cy, shadow_ray);
		if (t > EPSILON && t < light_dist)
			return (1);
		cur = cur->next;
	}
	return (0);
}

void	illuminate_obj(t_rgb *final_col, t_mrt *m, t_inter *i)
{
	t_rgb	ambient = m->scene->amb_light.color;
	t_rgb	*obj_col;

	//aplly ambient light
	get_obj_color(&obj_col, i);
	mult_scalar_colors(&ambient, &m->scene->amb_light.color,
		m->scene->amb_light.ratio);
	multi_colors(final_col, &ambient, obj_col);
	t_tup	light_dir;
	sub_tuples(light_dir, m->scene->light.position, i->hit_point);
	normalize(light_dir);
	double	cos_theta;
	cos_theta = dot_prod(i->normal, light_dir);
	if (cos_theta < 0)
		cos_theta = 0;
	cos_theta = 0.1 + (1 - 0.1) * cos_theta;
	if (is_in_shadow(m, i))
	{
		color_range(final_col);
		return ;
	}
	t_rgb diffuse_color;
	mult_scalar_colors(&diffuse_color, obj_col, cos_theta * m->scene->light.bright_ratio);
	add_colors(final_col, final_col, &diffuse_color);
	t_tup view_dir;
	sub_tuples(view_dir, m->scene->camera.position, i->hit_point);
	normalize(view_dir);
 	t_tup reflect_dir;
	t_tup neg_light;
	multi_tuple(neg_light, light_dir, -1);
	reflect(reflect_dir, neg_light, i->normal);
	double spec_angle = dot_prod(reflect_dir, view_dir);
	if(spec_angle < 0) 
		spec_angle = 0;
	double shininess = 100;
	double spec_intensity = pow(spec_angle, shininess);
	add_to_color(final_col, final_col, ((double)255 * spec_intensity));
	color_range(final_col);
}

void	render_obj(t_mrt *m, t_inter *i, int x, int y)
{
	t_tup	scaled;
	t_rgb	final_color;

	multi_tuple(scaled, m->ray.direction, i->t);
	add_tuples(i->hit_point, m->ray.origin, scaled);
	if (i->obj->typ == SPHERE)
		normal_at(i->normal, i->obj->sp.pos, i->hit_point);
	normalize(i->normal);
	if (dot_prod(i->normal, m->ray.direction) > 0)
	multi_tuple(i->normal, i->normal, -1);
	illuminate_obj(&final_color, m, i);
	mlx_put_pixel(m->image, x, y, get_rgba(&final_color,
			m->scene->light.bright_ratio));
}

void	calc_intersections(t_inter **list, t_inter *new)
{
	t_inter	*cur;

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

void	canvas(t_mrt *m)
{
	uint32_t	x;
	uint32_t	y;
	t_tup		direction;
	t_view		view;
	t_inter		*i = NULL;

	normalize(m->scene->camera.orientation_vector);
	translate_objects(m);
	project_objects(m);
	setup_viewport(&view, m);
	y = 0;
	while (y < m->image->height)
	{
		x = 0;
		while (x < m->image->width)
		{
			calc_direction(direction,
				m->scene->camera.orientation_vector,
				(x * view.pitch_delta) - view.pitch_start,
				(y * view.roll_delta) - view.roll_start);
			create_ray(&m->ray, m->scene->camera.position, direction);
			t_inter	*inter = NULL;
			t_list *current = m->obj;
			while (current)
			{
				t_obj *obj = current->content;
				double t = -1;
				if (obj->typ == SPHERE)
					t = inter_sphere(obj->sp, m->ray);
				if (obj->typ == PLANE)
					t = inter_plane(obj->pl, m->ray);
				// if (obj->typ == CYLINDER)
				// 	t = inter_cylinder(obj->sp, m->ray);
				if (t > 0)
				{	
					i = malloc(sizeof(t_inter));
					i->t = t;
					i->obj = obj;
					i->next = NULL;
					calc_intersections(&inter, i);
				}
				current = current->next;
			}
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
