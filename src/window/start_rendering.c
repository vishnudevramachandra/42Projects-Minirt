/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_rendering.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 16:31:36 by majkijew          #+#    #+#             */
/*   Updated: 2026/01/26 17:42:50 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_color(t_rgb *c)
{
	if (!c)
		return ;
	printf("Color: R=%.2d, G=%.2d, B=%.2d\n", c->r, c->g, c->b);
}

void	render_obj(t_mrt *m, t_inter *i, int x, int y)
{
	t_tup	scaled;
	t_rgb	final_color = (t_rgb){0,0,0};

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
			if (0 < dot_prod(
					*perpvec_to_plane(vec, &obj->pl, (double[4]){0, 0, 0, 1}),
				obj->pl.norm_vec))
				multi_tuple(obj->pl.norm_vec, obj->pl.norm_vec, -1);
		}
		else if (obj->typ == CYLINDER)
			normalize(obj->cy.axis);
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
			t = inter_sphere(&obj->sp, &m->ray);
		else if (obj->typ == PLANE)
			t = inter_plane(&obj->pl, &m->ray);
		if (obj->typ == CONE)
			t = inter_cone(obj->co, m->ray);
		else if (obj->typ == CYLINDER)
			t = inter_cylinder(&obj->cy, &m->ray);
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
