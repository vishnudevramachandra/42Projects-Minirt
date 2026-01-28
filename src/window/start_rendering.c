/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_rendering.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 16:31:36 by majkijew          #+#    #+#             */
/*   Updated: 2026/01/28 16:56:09 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	render_obj(t_mrt *m, t_inter *i, int x, int y)
{
	t_tup	scaled;
	t_rgb	final_color;

	final_color = (t_rgb){0, 0, 0};
	if (0 < i->t0)
		multi_tuple(scaled, m->ray.direction, i->t0);
	else
		multi_tuple(scaled, m->ray.direction, i->t1);
	// multi_tuple(scaled, m->ray.direction, i->t);
	add_tuples(i->hit_point, m->ray.origin, scaled);
	normal_at(i->normal, i->obj, i->hit_point);
	final_obj_light(&final_color, m, i);
	mlx_put_pixel(m->image, x, y, get_rgba(&final_color, 1));
}

void	inter_obj(double *t, t_obj *obj, t_ray *ray)
{
	if (obj->typ == SPHERE)
		inter_sphere(t, &obj->sp, ray);
	else if (obj->typ == PLANE)
		inter_plane(t, &obj->pl, ray);
	else if (obj->typ == CYLINDER)
		inter_cylinder(t, &obj->cy, ray);
	else if (obj->typ == CONE)
		inter_cone(t, &obj->co, ray);
}

void	compute_intersections(t_inter **inter, t_mrt *m)
{
	t_list	*current;
	t_obj	*obj;
	double	t[2];

	current = m->obj;
	while (current)
	{
		obj = current->content;
		inter_obj(t, obj, &m->ray);
		if (0 < t[0] || 0 < t[1])
			insert_intersection(inter, malloc(sizeof(t_inter)), obj, t);
		current = current->next;
	}
}

void	canvas_loop(t_mrt *m, uint32_t	x, uint32_t y, t_view view)
{
	t_inter		*inter;

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
}

void	canvas(t_mrt *m)
{
	uint32_t	x;
	uint32_t	y;
	t_view		view;

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
			canvas_loop(m, x, y, view);
			x++;
		}
		y++;
	}
}
