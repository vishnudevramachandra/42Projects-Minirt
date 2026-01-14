/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 15:59:29 by majkijew          #+#    #+#             */
/*   Updated: 2026/01/14 13:28:54 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rgb(int a, int b, int c, int d)
{
	return (a << 24 | b << 16 | c << 8 | d);
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

void	color_range(t_rgb *c)
{
	if (c->r > 255)
		c->r = 255;
	if (c->g > 255)
		c->g = 255;
	if (c->b > 255)
		c->b = 255;
}