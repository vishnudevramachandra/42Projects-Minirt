/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:42:07 by majkijew          #+#    #+#             */
/*   Updated: 2026/01/22 17:51:40 by majkijew         ###   ########.fr       */
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
	init_point(scene->camera.position, NAN, NAN, NAN);
	init_vector(scene->camera.orientation_vector, -2, -2, -2);
	scene->camera.horizontal_field = -1;
	// scene->light.bright_ratio = -1;
	// scene->light.color = (t_rgb){-1, -1, -1};
}

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
	printf("before init_scene\n");
	init_scene(mrt->scene);
	printf("before read_from_fd\n");
	read_from_fd(av[1], mrt->scene, &mrt->obj);
	printf("before init_mrt\n");
	t_list *n = mrt->scene->lights_list;
	int count = 0;
	while (n) { count++; n = n->next; }
	printf("DEBUG: %d lights in scene\n", count);

	init_mrt(mrt);
}
