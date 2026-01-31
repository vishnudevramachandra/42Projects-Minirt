/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 10:20:19 by vramacha          #+#    #+#             */
/*   Updated: 2026/01/31 15:22:34 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	normalize_helper(t_obj *obj)
{
	t_tup	vec;

	if (obj->typ == PLANE)
	{
		normalize(obj->pl.norm_vec);
		if (0 < dot_prod(
				*perpvec_to_plane(vec, &obj->pl, (double [4]){0, 0, 0, 1}),
			obj->pl.norm_vec))
			multi_tuple(obj->pl.norm_vec, obj->pl.norm_vec, -1);
	}
	else if (obj->typ == CYLINDER)
		normalize(obj->cy.axis);
	else if (obj->typ == CONE)
		init_vector(obj->co.axis, 0, 1, 0);
}

// those vectors that are supposed to be normal vectors are normalized
void	normalize_vectors(t_mrt *m)
{
	t_list	*cur;
	t_obj	*obj;
	t_tup	origin;

	init_point(origin, 0, 0, 0);
	normalize(m->scene->camera.orientation_vector);
	if (!m->obj)
		return ;
	cur = m->obj;
	while (cur)
	{
		obj = cur->content;
		normalize_helper(obj);
		cur = cur->next;
	}
}
