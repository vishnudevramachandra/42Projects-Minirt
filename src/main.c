/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:42:07 by majkijew          #+#    #+#             */
/*   Updated: 2025/11/17 17:57:46 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minirt.h"

int	lstrncmp(char *str, char *str2, int c)
{
	int	len;
	int	point;
	int	i;

	i = 0;
	len = ft_strlen(str);
	point = len - c;
	while (i < c)
	{
		if (str[point] != str2[i])
			return (1);
		i++;
		point++;
	}
	return (0);
}

void	init_scene(t_scene *scene)
{
	scene->amb_light.ratio = -1;
	scene->amb_light.color = (t_rgb){-1, -1, -1};
	scene->camera.position = (t_tup){NAN, NAN, NAN, NAN};
	scene->camera.orientation_vector = (t_tup){-2, -2, -2, -2};
	scene->camera.horizontal_field = -1;
	scene->light.position = (t_tup){NAN, NAN, NAN, NAN};
	scene->light.bright_ratio = -1;
	scene->light.color = (t_rgb){-1, -1, -1};
}

// void	free_mem(t_scene *scene, t_list *objs, t_mlx *mlx)
// {
// 	(void)scene;
// 	(void)objs;
// 	mlx_terminate(mlx->mlx);
// }

int32_t	main(int ac, char **av)
{
	t_mrt	*mrt;

	if (ac != 2)
		erro_msg("ERROR", 1);
	if (lstrncmp(av[1], ".rt", 3))
		erro_msg("ERROR", 1);
	mrt = malloc(sizeof(t_mrt));
	if (!mrt)
		erro_msg("ERROR", 1);
	mrt->scene = malloc(sizeof(t_scene));
	if (!mrt->scene)
		erro_msg("ERROR", 1);
	init_scene(mrt->scene);
	read_from_fd(av[1], mrt->scene, &mrt->objs);
	init_mrt(mrt);
	// free_mem();
}
