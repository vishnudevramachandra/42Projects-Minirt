/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_inter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:16:55 by vramacha          #+#    #+#             */
/*   Updated: 2025/12/12 15:29:15 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../Includes/minirt.h"

int	main()
{
	t_ray	r = {.origin={0, 1, 0, 1}, .direction={0, -1, 0, 0}};
	t_plane	pl = {.point={0, 0, 0, 1}, .norm_vec={1, 0, 0, 0}, .color={.r=255, .g=255, .b=255}};

	printf("%f\n", inter_plane(&pl, &r));
}