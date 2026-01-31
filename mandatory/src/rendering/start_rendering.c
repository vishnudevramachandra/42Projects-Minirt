/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_rendering.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 16:31:36 by majkijew          #+#    #+#             */
/*   Updated: 2026/01/31 03:32:37 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	render_obj(t_mrt *m, t_inter *i, int x, int y)
{
	t_tup	scaled;
	t_rgb	final_color;

	final_color = (t_rgb){0, 0, 0};
	if (0 <= i->t0)
		multi_tuple(scaled, m->ray.direction, i->t0);
	else
		multi_tuple(scaled, m->ray.direction, i->t1);
	add_tuples(i->hit_point, m->ray.origin, scaled);
	normal_at(i->normal, i->obj, i->hit_point);
	final_obj_color(&final_color, m, i);
	printf("babis grzywka\n");
	mlx_put_pixel(m->image, x, y, get_rgba(&final_color, 1));
}

void	compute_intersections(t_inter **inter, t_mrt *m)
{
	t_list	*current;
	t_obj	*obj;
	t_inter	*new;
	double	t[2];

	current = m->obj;
	while (current)
	{
		obj = current->content;
		inter_obj(t, obj, &m->ray);
		if (0 < t[0] || 0 < t[1])
		{
			printf("cos tu\n??");
			new = malloc(sizeof(t_inter));
			if (!new)
				return ;
			insert_intersection(inter, new, obj, t);
			printf("wracam i co??\n");
		}
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
		printf("am i hhere??\n");
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
	translate_objects_and_lights(m);
	project_objects_and_lights(m);
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
