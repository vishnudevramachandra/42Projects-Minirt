/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_rays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:12:14 by majkijew          #+#    #+#             */
/*   Updated: 2025/12/03 16:00:08 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//chapter 5

#include "minirt.h"
//						(origin)	(direction)
void	create_ray(t_ray *ray, t_tup point, t_tup vector)
{
	copy_tup(ray->origin, point);
	copy_tup(ray->direction, vector);
}

// t_tup	position(t_ray *ray, double t)
// {
// 	return ((t_tup){ray->origin[0] + ray->direction[0] * t,
// 		ray->origin[1] + ray->direction[1] * t,
// 		ray->origin[2] + ray->direction[2] * t,
// 		1});
// }

// void	position(t_tup position, t_ray *ray, double t)
// {
// 	init_point(position, 0, 0, 0);
// 	multi_tuple(position, ray, t);
// 	add_tuples(position, ray->origin, ray->direction);
// }
