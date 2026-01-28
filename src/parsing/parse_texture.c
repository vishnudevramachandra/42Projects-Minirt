/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:22:56 by vramacha          #+#    #+#             */
/*   Updated: 2026/01/28 14:14:56 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "minirt.h"

char	*read_filename(char *line, int *i)
{
    int		len;
    char	*filename;

    *i = 0 + len_spaces(line);
    len = 0;
    while (line[*i + len] && !ft_isspace(line[*i + len]))
        len++;
    filename = malloc(len + 1);
    if (!filename)
        return (NULL);
    ft_strlcpy(filename, line + *i, len + 1);
    filename[len] = '\0';
	*i = *i + len;
    printf("%s\n", filename);
    return (filename);
}

t_obj	*parse_texture(char *line, t_tex_type typ)
{
    int		i;
	t_obj	*obj;

	obj = malloc(sizeof(t_obj));
    if (!obj)
        return (NULL);
    obj->typ = TEXTURE;
    obj->tx.typ = typ;
    obj->tx.mlx_tex = mlx_load_png(read_filename(line, &i));
    if (!obj->tx.mlx_tex)
    {
        free(obj);
        return (NULL);
    }
    obj->tx.sp = parse_sphere(line + i);
    if (!obj->tx.sp)
    {
        mlx_delete_texture(obj->tx.mlx_tex);
        free(obj);
        return (NULL);
    }
    return (obj);
}