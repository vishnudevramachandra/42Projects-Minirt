/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:42:07 by majkijew          #+#    #+#             */
/*   Updated: 2026/02/01 14:07:10 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "minirt_bonus.h"

void	free_obj(void *content)
{
	t_obj	*obj;

	obj = content;
	if (obj->typ != TEXTURE)
		free(obj);
	else
		free_tx(obj);
}

void	clean_up(t_mrt *mrt)
{
	ft_lstclear(&mrt->scene->lights_list, free);
	ft_lstclear(&mrt->obj, free_obj);
	free(mrt->scene);
	free(mrt);
}

void	erro_clean(t_mrt *mrt, char *str, int v)
{
	ft_putstr_fd(str, v);
	ft_putstr_fd("\n", v);
	clean_up(mrt);
	exit (v);
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
