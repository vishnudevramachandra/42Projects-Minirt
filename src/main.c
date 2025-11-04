/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:42:07 by majkijew          #+#    #+#             */
/*   Updated: 2025/11/04 13:43:47 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	scene->camera.position = (t_vec){NAN, NAN, NAN};
	scene->camera.orientation_vector = (t_vec){-2, -2, -2};
	scene->camera.horizontal_field = -1;
	scene->light.position = (t_vec){NAN, NAN, NAN};
	scene->light.bright_ratio = -1;
	scene->light.color = (t_rgb){-1, -1, -1};
}

int	main(int ac, char **av)
{
	t_scene	*scene;
	// mlx_t	mlx;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		erro_msg("ERROR", 1);
	if (ac != 2)
		return (1);
	if (lstrncmp(av[1], ".rt", 3)) //custom strncmp to check if the last 3 characters are .rt
		erro_msg("ERROR", 1);
	init_scene(scene);
	// init_mlx(); ?? 
	read_from_fd(av[1], scene);
}
	// first we would if we have 2 argumenst 
	// the name of the program and file.rt 

	// the we check if the rt exists

	// first we look for the specifires A | C | L (sp, pl, cy);

	// so we have t ocheck if the a c l is in the right range if no exit errormsg 

	// the we checkl wich kind of figure we have 

	// this is the basci parsing^
	
	// basci math functions 