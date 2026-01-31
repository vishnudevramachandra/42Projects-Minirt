/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 18:21:52 by vramacha          #+#    #+#             */
/*   Updated: 2026/01/31 15:20:36 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

double	delta(double a, double b_h, double c)
{
	return ((b_h * b_h) - (a * c));
}

void	get_hitpoints(double *t, double a, double b_h, double sqrt_dlt)
{
	double	tmp;

	t[0] = (-b_h - sqrt_dlt) / a;
	t[1] = (-b_h + sqrt_dlt) / a;
	if (t[1] < t[0])
	{
		tmp = t[0];
		t[0] = t[1];
		t[1] = tmp;
	}
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
	else if (obj->typ == TEXTURE)
		inter_obj(t, obj->tx.sub_obj, ray);
}
