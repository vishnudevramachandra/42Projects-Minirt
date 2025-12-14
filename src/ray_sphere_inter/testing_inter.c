/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_inter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:16:55 by vramacha          #+#    #+#             */
/*   Updated: 2025/12/14 13:03:46 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../Includes/minirt.h"

int	main()
{
	double	t;
	t_plane	pl = {.point={0, 0, 1, 1}, .norm_vec={0, -1/sqrt(2), -1/sqrt(2), 0},
		.color={.r=255, .g=255, .b=255}};

	t_ray	r1 = {.origin={0, 0, 0, 1}, .direction={0, -1/sqrt(2), 1/sqrt(2), 0}};
	t = inter_plane(&pl, &r1);
	printf("%f [%i]\n", t, t<0); // -inf [1]

	t_ray	r2 = {.origin={0, 0, 0, 1}, .direction={0, -1/sqrt(2), -1/sqrt(2), 0}};
	t = inter_plane(&pl, &r2);
	printf("%f [%i]\n", t, t<0); // -0.707107 [1]

	t_ray	r3 = {.origin={0, 0, 0, 1}, .direction={0, 1/sqrt(2), 1/sqrt(2), 0}};
	t = inter_plane(&pl, &r3);
	printf("%f [%i]\n", t, t<0); // -0.707107 [1]
}