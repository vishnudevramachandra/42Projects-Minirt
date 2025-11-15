/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_prod.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 15:01:54 by majkijew          #+#    #+#             */
/*   Updated: 2025/11/15 15:26:44 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "../../Includes/minirt.h"

double	dot_prod(t_vec a, t_vec b)
{
	return (a.x * b.x
		+ a.y * b.y
		+ a.z * b.z
		+ a.w * b.w);
}

t_vec	cross_prod(t_vec a, t_vec b)
{
	t_vec	cp;

	cp.x = a.y * b.z - a.z * b.y;
	cp.y = a.z * b.x - a.x * b.z;
	cp.z = a.x * b.y - a.y * b.x;
	return (cp);
}
