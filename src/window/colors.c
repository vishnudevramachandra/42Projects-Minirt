/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 15:59:29 by majkijew          #+#    #+#             */
/*   Updated: 2025/11/20 22:36:03 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rgb(int a, int b, int c)
{
	return (a << 24 | b << 16 | c << 8 | 1);
}
// okej czyli kolory sa jednym tupletem i musimy teraz ogarnac jak zamienc ten tuplet zeby mial wartosc hexadecymelowal zeby moc uzywac ich w naszych funkcjach mlx?

/// @brief Colors are commonly represented as 4-byte integers. This 4-byte integer 
// is a grouping of four individual channels: red, green, blue and alpha, with alpha representing transparency.
// Additionally, colors are usually shown in hexadecimal to make each channel value identifiable:
/// @param c color 
/// @param a brightness ratio
/// @return 
int	get_rgba(t_rgb *c, double a)
{
	unsigned int	alpha;

	alpha = (int)(a * 255);
	if (alpha < 0)
		alpha = 0;
	if (alpha > 255)
		alpha = 255;
	// printf("r=%d\n g=%d\n b=%d\n a=%d\n", c->r, c->g, c->b, alpha);
	return (c->r << 24 | c->g << 16 | c->b << 8 | alpha);
}

//adding colors
t_rgb	add_colors(t_rgb *c1, t_rgb *c2)
{
	t_rgb	c3;

	c3.r = c2->r + c1->r;
	c3.g = c2->g + c1->g;
	c3.b = c2->b + c1->b;
	return (c3);
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
t_rgb	mult_scalar_colors(t_rgb *c1, double scalar)
{
	t_rgb	c2;

	c2.r = c1->r * scalar;
	c2.g = c1->g * scalar;
	c2.b = c1->b * scalar;
	return (c2);
}

//multiply color by another color this is used to bledn two colors toghether 
//This method of blending two colors works by multiplying corresponding
// components of each color to form a new color. It’s technically called the
// Hadamard product 
t_rgb	multi_colors(t_rgb *c1, t_rgb *c2)
{
	t_rgb	c3;

	c3.r = c2->r * c1->r;
	c3.g = c2->g * c1->g;
	c3.b = c2->b * c1->b;
	return (c3);
}
// void	canvas(int )