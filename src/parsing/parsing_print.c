/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:56:48 by vramacha          #+#    #+#             */
/*   Updated: 2025/11/05 22:35:35 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../Includes/minirt.h"

static void print_vec(t_vec *vec)
{
    printf("     %g,%g,%g", vec->x, vec->y, vec->z);
}

static void print_color(t_rgb *rgb)
{
    printf("     %i,%i,%i", rgb->r, rgb->g, rgb->b);
}

static void print_sp(t_sphere  *sp)
{
    printf("sp");
    print_vec(&sp->pos);
    printf("    %g", sp->dia);
    print_color(&sp->color);
    printf("\n");
}

static void print_pl(t_plane  *pl)
{
    printf("pl");
    print_vec(&pl->point);
    print_vec(&pl->norm_vec);
    print_color(&pl->color);
    printf("\n");
}

static void print_cy(t_cylinder  *cy)
{
    printf("cy");
    print_vec(&cy->pos);
    print_vec(&cy->axis);
    printf("    %g", cy->dia);
    printf("    %g", cy->height);
    print_color(&cy->color);
    printf("\n");
}

void    print_obj(t_list *objs)
{
    t_obj   *obj;

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
