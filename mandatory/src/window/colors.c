/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 15:59:29 by majkijew          #+#    #+#             */
/*   Updated: 2026/01/26 18:13:08 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rgb(int a, int b, int c, int d)
{
	return (a << 24 | b << 16 | c << 8 | d);
}

int	get_rgba(t_rgb *c, double a)
{
	unsigned int	alpha;

	alpha = (int)(a * 255);
	if (alpha < 0)
		alpha = 0;
	if (alpha > 255)
		alpha = 255;
	return (c->r << 24 | c->g << 16 | c->b << 8 | alpha);
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
