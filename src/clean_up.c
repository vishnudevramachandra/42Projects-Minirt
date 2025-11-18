/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:28:56 by majkijew          #+#    #+#             */
/*   Updated: 2025/11/18 18:01:47 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


void	free_objs(void *content)
{
	free(content);
}

void	free_mem(t_mrt *mrt)
{
	if (!mrt)
		return ;

	if (mrt->scene)
	{
		free(mrt->scene);
		mrt->scene = NULL;
	}
	if (mrt->objs)
	{
		ft_lstclear(&mrt->objs, free_objs);
		mrt->objs = NULL;
	}
	// if (mrt->mlx)
	// {
	// 	if (mrt->image)
	// 	{
	// 		mlx_delete_image(mrt->mlx, mrt->image);
	// 		mrt->image = NULL;
	// 	}
	// 	mlx_terminate(mrt->mlx);
	// 	mrt->mlx = NULL;
	// }
	free(mrt);
}
