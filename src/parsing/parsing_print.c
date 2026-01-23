/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:56:48 by vramacha          #+#    #+#             */
/*   Updated: 2026/01/22 18:34:20 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../Includes/minirt.h"

void	print_tup(t_tup vec)
{
	printf("     %g,%g,%g,%g", vec[0], vec[1], vec[2], vec[3]);
}

static void	print_color(t_rgb *rgb)
{
	printf("     %i,%i,%i", rgb->r, rgb->g, rgb->b);
}

static void	print_sp(t_sphere *sp)
{
	printf("sp");
	print_tup(sp->pos);
	printf("    %g", sp->dia);
	print_color(&sp->mt.pattern.color1);
	printf("\n");
}

static void	print_pl(t_plane *pl)
{
	printf("pl");
	print_tup(pl->point);
	print_tup(pl->norm_vec);
	print_color(&pl->mt.pattern.color1);
	printf("\n");
}

static void	print_cy(t_cylinder *cy)
{
	printf("cy");
	print_tup(cy->pos);
	print_tup(cy->axis);
	printf("    %g", cy->dia);
	printf("    %g", cy->height);
	print_color(&cy->mt.pattern.color1);
	printf("\n");
}

void	print_obj(t_list *objs)
{
	t_obj	*obj;

	while (objs)
	{
		obj = objs->content;
		if (obj->typ == SPHERE)
			print_sp(&obj->sp);
		else if (obj->typ == PLANE)
			print_pl(&obj->pl);
		else
			print_cy(&obj->cy);
		objs = objs->next;
	}
}
