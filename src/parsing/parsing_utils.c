/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:19:54 by majkijew          #+#    #+#             */
/*   Updated: 2025/11/04 13:43:29 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_vector(t_vec *v, int j, double value)
{
	if (j < 1)
		v->x = value;
	else if (j < 2)
		v->y = value;
	else
		v->z = value;
}

void	set_color(t_rgb *c, int j, int value)
{
	if (j < 1)
		c->r = value;
	else if (j < 2)
		c->g = value;
	else
		c->b = value;
}
