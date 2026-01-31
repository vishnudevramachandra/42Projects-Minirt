/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_arith.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 18:11:13 by vramacha          #+#    #+#             */
/*   Updated: 2026/01/26 18:11:40 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minirt.h"

//adding colors
void	add_colors(t_rgb *new_c, t_rgb *c1, t_rgb *c2)
{
	new_c->r = c2->r + c1->r;
	new_c->g = c2->g + c1->g;
	new_c->b = c2->b + c1->b;
}

void	add_to_color(t_rgb *new_c, t_rgb *c1, double comp)
{
	new_c->r = c1->r + comp;
	new_c->g = c1->g + comp;
	new_c->b = c1->b + comp;
}

//substract colors
t_rgb	sub_colors(t_rgb *c1, t_rgb *c2)
{
	t_rgb	c3;

	c3.r = c2->r - c1->r;
	c3.g = c2->g - c1->g;
	c3.b = c2->b - c1->b;
	return (c3);
}

//multiply colors by a scalar
//musze przeczytac co to wielksoc skalarna w przykladzie bylo przez 2
void	mult_scalar_colors(t_rgb *new_c, t_rgb *old_c, double scalar)
{
	new_c->r = old_c->r * scalar;
	new_c->g = old_c->g * scalar;
	new_c->b = old_c->b * scalar;
}

//multiply color by another color this is used to bledn two colors toghether 
//This method of blending two colors works by multiplying corresponding
// components of each color to form a new color. It’s technically called the
// Hadamard product 
void	multi_colors(t_rgb	*c_new, t_rgb *c1, t_rgb *c2)
{
	c_new->r = (c1->r / 255.0) * c2->r;
	c_new->g = (c1->g / 255.0) * c2->g;
	c_new->b = (c1->b / 255.0) * c2->b;
}
