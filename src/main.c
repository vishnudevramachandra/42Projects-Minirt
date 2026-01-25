/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:42:07 by majkijew          #+#    #+#             */
/*   Updated: 2026/01/25 15:08:00 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minirt.h"

int32_t	main(int ac, char **av)
{
	t_mrt	*mrt;

	check_arguments(ac, av);
	mrt = malloc(sizeof(t_mrt));
	if (!mrt)
		erro_msg("ERROR", 1);
	mrt->scene = malloc(sizeof(t_scene));
	if (!mrt->scene)
		erro_msg("ERROR", 1);
	init_scene(mrt->scene);
	read_from_fd(av[1], mrt->scene, &mrt->obj);
	init_mrt(mrt);
}
