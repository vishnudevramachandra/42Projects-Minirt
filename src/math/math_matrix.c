/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:43:04 by vramacha          #+#    #+#             */
/*   Updated: 2025/11/18 18:38:58 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../Includes/minirt.h"

typedef double  mat4[4][4];

void print_vec(double v[])
{
    printf("Vec: (%g,%g,%g,%g)\n", v[0], v[1], v[2], v[3]);
}

void    multi_mat(mat4 res, mat4 a, mat4 b)
{
    int     i;
    int     j;
    t_tup   v;

    i = 0;
    while (i++ < 4)
    {
        j = 0;
        while (j++ < 4)
        {
            multi_tuple(b[j]);
            j++;
        }
    }
}

int main(void)
{
    mat4    m = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 6}, {5, 4, 3, 2}};
    mat4    res = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    mat4    n;
    
    multi_mat(res, n, m);
}