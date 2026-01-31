/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 18:23:43 by vramacha          #+#    #+#             */
/*   Updated: 2026/01/28 15:28:52 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minirt.h"

// compute the perpendicular vector from the user-defined origin to the plane
t_tup	*perpvec_to_plane(t_tup vec, t_plane *pl, t_tup origin)
{
	double	m;

	sub_tuples(vec, pl->point, origin);
	m = dot_prod(pl->norm_vec, vec);
	multi_tuple(vec, pl->norm_vec, m);
	return ((t_tup *)vec);
}

void	inter_plane(double *t, t_plane *pl, t_ray *r)
{
	t_tup	perp_vec;

	perpvec_to_plane(perp_vec, pl, r->origin);
	if (fabs(dot_prod(r->direction, perp_vec)) < __DBL_EPSILON__)
	{
		t[0] = -INFINITY;
		t[1] = -INFINITY;
	}
	else
	{
		t[0] = dot_prod(perp_vec, perp_vec) / dot_prod(r->direction, perp_vec);
		t[1] = t[0];
	}
}
