/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 21:20:30 by vramacha          #+#    #+#             */
/*   Updated: 2026/01/31 15:21:51 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

char	*read_filename(char *line, int *i)
{
	int		len;
	char	*filename;

	len = 0;
	while (line[*i + len] && !ft_isspace(line[*i + len]))
		len++;
	filename = malloc(len + 1);
	if (!filename)
		return (NULL);
	ft_strlcpy(filename, line + *i, len + 1);
	filename[len] = '\0';
	*i = *i + len;
	return (filename);
}

t_obj	*create_and_init_tex_obj(t_tex_type typ)
{
	t_obj	*obj;

	obj = malloc(sizeof(t_obj));
	if (!obj)
		return (NULL);
	obj->typ = TEXTURE;
	obj->tx.typ = typ;
	obj->tx.mlx_tex = NULL;
	obj->tx.img = NULL;
	obj->tx.mlx_tex_b = NULL;
	obj->tx.bump_img = NULL;
	obj->tx.sub_obj = NULL;
	return (obj);
}
