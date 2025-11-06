/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:16:44 by majkijew          #+#    #+#             */
/*   Updated: 2025/11/06 09:57:31 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "minirt.h"
#include "parse.h"

//TO DO OF PARSING THE SCENE
// norm.... ❌ TODO
//
//FILE:
//1)correct type file (.rt)? ✅
//
//2)empty file? ✅ 
//^(u might want to check i mean for now at the begginig i am 
//assigning in the init scene that if the value will be asign inncorectlly 
//therefore if there is no value its out of range so i guess it should work??)
//
//3)incorrect file? (idk i guess its done but just idk what do they mean)
//
//SCENE:
//1)Verify that the id(first word) is correct: A, C, L, pl, sp or cy ONLY ❌ TODO 
//2)Verift that each element has the correct number of params 50/50 ❌ TODO
//-mandatory = A: 3, C: 4, L: 3, sp: 4, pl: 4, cy: 6
//------so for now we just make sure that it has at least the numbers of the elements
//------that it should but there is no max 
//
//ELEMENTS: (analyze the line of each element and put it in a structure)
//1) CAMERA ✅
//
//2)OBJECTS
//-plane ✅ TODO
//-sphere ✅ TODO
//-cylinder ✅ TODO
//
// 3)Lights
// -ambience ✅
// -point of light ✅

// There is a MAXIMUM of one camera, one diffused light and one ambient light (there can be 0 or one, but no more!)
// ok so with that my solution in the init_scene with assigning it first with inncorect values my not be the besttt 
// but idk something to think abt bc i think its good for some solutionsss 

//if A exists it should have 3 parametes no more no less 


bool	scene_range(t_amb_light a, t_camera c, t_light l)
{
	if (a.ratio < 0 || a.ratio > 1)
		return (false);
	else if ((a.color.r < 0 || a.color.r > 255) || (a.color.g < 0
			|| a.color.g > 255) || (a.color.b < 0 || a.color.b > 255))
		return (false);
	else if (c.position.x == NAN || c.position.y == NAN || c.position.z == NAN)
		return (false);
	else if ((c.orientation_vector.x < -1 || c.orientation_vector.x > 1)
		|| (c.orientation_vector.y < -1 || c.orientation_vector.y > 1)
		|| (c.orientation_vector.z < -1 || c.orientation_vector.z > 1))
		return (false);
	else if (c.horizontal_field < 0 || c.horizontal_field > 180)
		return (false);
	else if (l.position.x == NAN || l.position.y == NAN || l.position.z == NAN)
		return (false);
	else if (l.bright_ratio < 0 || l.bright_ratio > 1)
		return (false);
	else if ((l.color.r < 0 || l.color.r > 255) || (l.color.g < 0
			|| l.color.g > 255) || (l.color.b < 0 || l.color.b > 255))
		return (false);
	else
		return (true);
}

// // verify that the id(first worf is correct A, C, L, pl, sp, cy NOTHING ELSE)
// bool	verify_if(char *line, int i)
// {
// 	if (i > 0)
// 		return (true);
// 	if((ft_strncmp(line, "A ") 1)|| )
// }

int	is_scene(char *line)
{
	if ((line[0] == 'A' && line[1] == ' ')
		|| (line[0] == 'C' && line[1] == ' ')
		|| (line[0] == 'L' && line[1] == ' '))
		return (1);
	return (0);
}

int	is_object(char *line)
{
	if ((line[0] == 's' && line[1] == 'p' && line[2] == ' ')
		|| (line[0] == 'c' && line[1] == 'y' && line[2] == ' ')
		|| (line[0] == 'p' && line[1] == 'l' && line[2] == ' '))
		return (1);
	return (0);
}

void	fill_scene(t_scene *scene, char *line)
{
	if (line[0] == 'A')
		scene->amb_light = amb_light(line + 1, scene->amb_light);
	else if (line[0] == 'C')
		scene->camera = camera(line + 1, scene->camera);
	else if (line[0] == 'L')
		scene->light = light(line + 1, scene->light);
}

void	read_from_fd(char *file_name, t_scene *scene, t_list **objs)
{
	int		fd;
	char	*line;
	int		i;

	*objs = NULL;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		erro_msg("ERROR", 1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		// if (verify_id(line + i, i) == false) //verify that the id(first worf is correct A, C, L, pl, sp, cy NOTHING ELSE)
		// 	erro_msg("ERROR", STDERR_FILENO); //clean and return
		i = 0 + len_spaces(line);
		if (line[i] == '\n')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (is_scene(line + i))
			fill_scene(scene, line + i);
		else if (!is_object(line + i) || !parse_obj(line + i, objs))
		{
			free(line);
			erro_msg("ERROR", STDERR_FILENO);
		}
		free(line);
		line = get_next_line(fd);
	}
	print_obj(*objs);
	close(fd);
	if (scene_range(scene->amb_light, scene->camera, scene->light) == false)
		erro_msg("INCORRECT RANGE", STDERR_FILENO); // free and exit
	//if everything is correct with that part procceed to parse the figures
	// printf("great success\n");
}
