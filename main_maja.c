/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_maja.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 16:10:11 by majkijew          #+#    #+#             */
/*   Updated: 2025/11/01 19:09:12 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minirt.h"

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

int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	if (lstrncmp(av[1], ".rt", 3)) //custom strncmp to check if the last 3 characters are .rt
		return (1);
	read_from_fd(av[1]);

	// char *line;

	// int i;
	// while ((line = get_next_line(fd)) != NULL)
	// {
	// 	i = 0;
	// 	while(line[i])
	// 	{
	// 		if (line[i] == 'A')
	// 			amb_light(line[i]);
	// 		else if (line[i] == 'C')
	// 			camera(line[i]);
	// 		else if (line[i] == 'L')
	// 			light(line[i]);
	// 		else
	// 			geo_figures(line[i]);
	// 	}
	// }
}
