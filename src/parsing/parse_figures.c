/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_figures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:57:51 by vramacha          #+#    #+#             */
/*   Updated: 2025/11/05 10:15:25 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "minirt.h"

size_t	strspn(const char *s, t_dataype dtype)
{
	size_t		i;
	size_t		tmp;
	const char	charset[] = "0123456789";

	i = 0;
	if (dtype == INT)
	{
		while (s[i])
		{
			if (!ft_strchr(charset, s[i]))
				break ;
			i++;
		}
	}
	else
	{
		i = strspn(s[i], INT);
		if (!i || (s[i] != '.'))
			return (0);
		tmp = strspn(s[i + 1], INT);
		if (!tmp)
			return (0);
		i += tmp;
	}
	return (i);
}

t_obj	*parse_sphere(char *line)
{
	int		i;
	int		j;
	t_obj	*obj;

	obj = malloc(sizeof(t_obj));
	if (!obj)
		return (NULL);
	obj->typ = SPHERE;
	i = 0;
	while (ft_isspace(line[i]))
		i++;
	j = 0;
	while (j < 3 && line[i] && line[i] != '\n')
	{
		if (strspn)
		set_color(&a.color, j, ft_atoi(&line[i]));
		while (line[i] >= '0' && line[i] <= '9')
			i++;
		if (line[i] == ',')
			i++;
		j++;
	}
	a.ratio = atod(&line[i]);
	while ((line[i] >= '0' && line[i] <= '9') || line[i] == '.')
		i++;
	while (ft_isspace(line[i]) && line[i] != '\n')
		i++;
	while (j < 3 && line[i] && line[i] != '\n')
	{
		set_color(&a.color, j, ft_atoi(&line[i]));
		while (line[i] >= '0' && line[i] <= '9')
			i++;
		if (line[i] == ',')
			i++;
		j++;
	}
	printf("ratio: %g\n", a.ratio);
	printf("colors: r=%d g=%d b=%d\n", a.color.r, a.color.g, a.color.b);
	return (a);
}

int	create_node_and_add_to_list(void *content, t_list **lst)
{
	t_list	*node;

	node = ft_lstnew(content);
	if (!node)
		return (0);
	ft_lstadd_back(lst, node);
	return (1);
}

t_list	*parse_obj(int fd)
{
	char	*line;
	t_list	*objs;
	t_obj	*obj;

	if (fd < 0)
		return (NULL);
	objs = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] == 's' && line[1] == 'p')
			obj = parse_sphere(line + 2);
		else if (line[0] == 'c' && line[1] == 'y')
			obj = parse_cylinder(line + 2);
		else if (line[0] == 'p' && line[1] == 'l')
			obj = parse_plane(line + 2);
		else
			return (ft_lstclear(&objs, free()), NULL);
		if (!obj || !create_node_and_add_to_list(obj, &objs))
			return (ft_lstclear(&objs, free()), NULL);
		free(line);
	}
	return (objs);
}
