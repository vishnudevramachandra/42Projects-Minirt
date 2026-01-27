/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:42:07 by majkijew          #+#    #+#             */
/*   Updated: 2026/01/27 18:32:17 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minirt.h"

void	erro_clean(t_mrt *mrt, char *str, int v)
{
	ft_putstr_fd(str, v);
	ft_putstr_fd("\n", v);
	ft_lstclear(&mrt->scene->lights_list, free);
	ft_lstclear(&mrt->obj, free);
	free(mrt->scene);
	free(mrt);
	exit (v);
}

void	clean_up(t_mrt *mrt)
{
	ft_lstclear(&mrt->scene->lights_list, free);
	ft_lstclear(&mrt->obj, free);
	free(mrt->scene);
	free(mrt);
}

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
	if (!read_from_fd(av[1], mrt->scene, &mrt->obj))
	{
		clean_up(mrt);
		erro_msg("Error", 1);
	}
	init_mrt(mrt);
	clean_up(mrt);
	return (0);
}
