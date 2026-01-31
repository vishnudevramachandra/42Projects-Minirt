/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_rays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:12:14 by majkijew          #+#    #+#             */
/*   Updated: 2026/01/31 15:52:11 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
//						(origin)	(direction)
void	create_ray(t_ray *ray, t_tup point, t_tup vector)
{
	copy_tup(ray->origin, point);
	copy_tup(ray->direction, vector);
}
