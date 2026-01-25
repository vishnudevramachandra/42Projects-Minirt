/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 15:03:30 by majkijew          #+#    #+#             */
/*   Updated: 2026/01/25 15:09:54 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//check if argv is *.rt type file
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

//assign false values for the scene
void	init_scene(t_scene *scene)
{
	scene->amb_light.ratio = -1;
	scene->amb_light.color = (t_rgb){-1, -1, -1};
	init_point(scene->camera.position, NAN, NAN, NAN);
	init_vector(scene->camera.orientation_vector, -2, -2, -2);
	scene->camera.horizontal_field = -1;
}

void	check_arguments(int ac, char **av)
{
	if (ac != 2)
		erro_msg("ERROR", 1);
	if (lstrncmp(av[1], ".rt", 3))
		erro_msg("ERROR", 1);
}
