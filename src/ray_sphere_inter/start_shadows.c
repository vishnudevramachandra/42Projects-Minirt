/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shadows.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:59:40 by majkijew          #+#    #+#             */
/*   Updated: 2025/11/27 15:44:42 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// void normal_at(t_obj x, t_tup)
							// various points on a sphere
void	normal_at(t_tup normal, t_tup sp_pos, t_tup point)
{
	sub_tuples(normal, point, sp_pos);
	normalize(normal);
}

void	render_light(t_mrt *m, uint32_t *x, uint32_t *y)
{
	double	px = (2.0 * (*x) / WIDTH - 1.0) * ((double)m->image->width / m->image->height);
	double	py = 1.0 - 2.0 * (*y) / m->image->height;
	t_ray	r;
	t_tup	direction;

	init_vector(direction, px, py, 1);
	create_ray(&r, m->scene->light.position, direction);
}
