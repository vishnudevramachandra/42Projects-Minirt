/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 15:03:30 by majkijew          #+#    #+#             */
/*   Updated: 2026/01/31 17:03:16 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	create_node_and_add_to_list(void *content, t_list **lst)
{
	t_list	*node;

	node = ft_lstnew(content);
	if (!node)
		return (0);
	ft_lstadd_back(lst, node);
	return (1);
}

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
	scene->amb_light.count = 0;
	scene->amb_light.ratio = -1;
	scene->amb_light.color = (t_rgb){-1, -1, -1};
	init_point(scene->camera.position, NAN, NAN, NAN);
	init_vector(scene->camera.orientation_vector, -2, -2, -2);
	scene->camera.horizontal_field = -1;
	scene->camera.count = 0;
	scene->lights_list = NULL;
}

void	check_arguments(int ac, char **av)
{
	if (ac != 2)
		erro_msg("ERROR", 1);
	if (lstrncmp(av[1], ".rt", 3))
		erro_msg("ERROR", 1);
}
