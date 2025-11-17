/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_prod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 15:01:54 by majkijew          #+#    #+#             */
/*   Updated: 2025/11/17 17:34:43 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "../../Includes/minirt.h"

double	dot_prod(t_tup a, t_tup b)
{
	return (a.x * b.x
		+ a.y * b.y
		+ a.z * b.z
		+ a.w * b.w);
}

t_tup	cross_prod(t_tup a, t_tup b)
{
	t_tup	cp;

	cp.x = a.y * b.z - a.z * b.y;
	cp.y = a.z * b.x - a.x * b.z;
	cp.z = a.x * b.y - a.y * b.x;
	return (cp);
}
// trick function to be implemented most of them need testing but idk