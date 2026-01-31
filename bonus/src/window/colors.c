/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 15:59:29 by majkijew          #+#    #+#             */
/*   Updated: 2026/01/31 15:23:39 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

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
