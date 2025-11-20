/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_rays->c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:12:14 by majkijew          #+#    #+#             */
/*   Updated: 2025/11/19 19:11:36 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//chapter 5

#include "minirt.h"
//						(origin)	(direction)
void	create_ray(t_ray *ray, t_tup point, t_tup vector)
{
	copy_point(ray->origin, point);
	copy_vector(ray->direction, vector);
}

// t_tup	position(t_ray *ray, double t)
// {
// 	return ((t_tup){ray->origin[0] + ray->direction[0] * t,
// 		ray->origin[1] + ray->direction[1] * t,
// 		ray->origin[2] + ray->direction[2] * t,
// 		1});
// }

void	position(t_tup position, t_ray *ray, double t)
{
	init_point(position, 0, 0, 0);
	multi_tuple(position, ray, t);
	add_tuples(position, ray->origin, ray->direction);
}
