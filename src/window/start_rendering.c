/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_rendering.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 16:31:36 by majkijew          #+#    #+#             */
/*   Updated: 2026/01/27 18:15:55 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	render_obj(t_mrt *m, t_inter *i, int x, int y)
{
	t_tup	scaled;
	t_rgb	final_color;

	final_color = (t_rgb){0, 0, 0};
	multi_tuple(scaled, m->ray.direction, i->t);
	add_tuples(i->hit_point, m->ray.origin, scaled);
	normal_at(i->normal, i->obj, i->hit_point);
	final_obj_light(&final_color, m, i);
	mlx_put_pixel(m->image, x, y, get_rgba(&final_color, 1));
}

void	compute_intersections(t_inter **inter, t_mrt *m,
			t_obj *obj, t_inter *new)
{
	t_list	*current;
	double	t;

	current = m->obj;
	while (current)
	{
		obj = current->content;
		t = -1;
		if (obj->typ == SPHERE)
			t = inter_sphere(&obj->sp, &m->ray);
		else if (obj->typ == PLANE)
			t = inter_plane(&obj->pl, &m->ray);
		else if (obj->typ == CONE)
			t = inter_cone(&obj->co, &m->ray);
		else if (obj->typ == CYLINDER)
			t = inter_cylinder(&obj->cy, &m->ray);
		if (0 < t)
		{
			new = malloc(sizeof(t_inter));
			if (!new)
				return ;
			insert_intersection(inter, new, obj, t);
		}
		current = current->next;
	}
}

void	canvas_loop(t_mrt *m, uint32_t	x, uint32_t y, t_view view)
{
	t_inter		*inter;
	t_obj		*obj;
	t_inter		*new;

	calc_direction(&m->scene->camera, &view, x, y);
	create_ray(&m->ray, m->scene->camera.position,
		m->scene->camera.orientation_vector);
	inter = NULL;
	obj = NULL;
	new = NULL;
	compute_intersections(&inter, m, obj, new);
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
