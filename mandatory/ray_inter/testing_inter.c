/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_inter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:16:55 by vramacha          #+#    #+#             */
/*   Updated: 2026/01/27 17:39:10 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include "../../Includes/minirt.h"

// int	main(void)
// {
// 	double	t;
// 	t_plane	pl = {.point = {0, 0, 1, 1},
// 		.norm_vec = {0, -1 / sqrt(2), -1 / sqrt(2), 0},
// 		.mt = {.shininess = 125,
// 			.pattern = {.color1 = {.r = 125, .b = 125, .g = 125},
// 						.fcn = NULL}}};
// 	// // -inf [1]
// 	// t_ray	r1 = {.origin = {0, 0, 0, 1},
// 	// 	.direction = {0, -1 / sqrt(2), 1 / sqrt(2), 0}};
// 	// t = inter_plane(&pl, &r1);
// 	// printf("%f [%i]\n", t, t < 0);
// 	// // -0.707107 [1]
// 	// t_ray	r2 = {.origin = {0, 0, 0, 1},
// 	// 	.direction = {0, -1 / sqrt(2), -1 / sqrt(2), 0}};
// 	// t = inter_plane(&pl, &r2);
// 	// printf("%f [%i]\n", t, t < 0);
// 	// // -0.707107 [1]
// 	// t_ray	r3 = {.origin = {0, 0, 0, 1},
// 	// 	.direction = {0, 1 / sqrt(2), 1 / sqrt(2), 0}};
// 	// t = inter_plane(&pl, &r3);
// 	// printf("%f [%i]\n", t, t < 0);

// 	t_cylinder cy = {.pos = {0.5, 5, 1.5, 1},
// 		.axis = {0, 1, 0, 0},
// 		.dia = 1,
// 		.height = 21.42,
// 		.mt = {.shininess = 125,
// 			.pattern = {.color1 = {.r = 125, .b = 125, .g = 125},
// 						.fcn = NULL}}};
// 	t_ray	r1 = {.origin = {0, 1, 1, 1},
// 		.direction = {1, 0, 0, 0}};
// 	normalize(r1.direction);
// 	t = inter_cylinder(&cy, &r1);
// 	printf("//"); print_tup(r1.direction); printf("//");
// 	printf("%f [%i]\n", t, t < 0);

// 	t_ray	r2 = {.origin = {0, 0, 1, 1},
// 		.direction = {1, -1 / sqrt(2), 1 / sqrt(2), 0}};
// 	normalize(r2.direction);
// 	t = inter_cylinder(&cy, &r2);
// 	printf("//"); print_tup(r2.direction); printf("//");
// 	printf("%f [%i]\n", t, t < 0);

// 	t_ray	r3 = {.origin = {0, 0, 1, 1},
// 		.direction = {1, -0.86602540378, 0.5, 0}};
// 	normalize(r3.direction);
// 	t = inter_cylinder(&cy, &r3);
// 	printf("//"); print_tup(r3.direction); printf("//");
// 	printf("%f [%i]\n", t, t < 0);

// 	t_ray	r4 = {.origin = {0, 0, 1, 1},
// 		.direction = {1, -200, 4, 0}};
// 	normalize(r4.direction);
// 	t = inter_cylinder(&cy, &r4);
// 	printf("//"); print_tup(r4.direction); printf("//");
// 	printf("%f [%i]\n", t, t < 0);
// }
