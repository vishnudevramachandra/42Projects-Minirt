/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:22:56 by vramacha          #+#    #+#             */
/*   Updated: 2026/01/30 14:28:48 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "minirt.h"

static char	*read_filename(char *line, int *i)
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

static void	assign_pix_val(t_rgb *img, uint32_t i, uint8_t *pixels, uint8_t *b)
{
	uint32_t	j;

	j = i * b[0];
	img[i].r = pixels[j];
	img[i].g = pixels[j + b[1]];
	img[i].b = pixels[j + (2 * b[1])];
}

static t_rgb	*texture_to_image(mlx_texture_t *mlx_tex)
{
	t_rgb		*img;
	uint32_t	h;
	uint32_t	w;
	uint8_t		bytes_factors[2];

	img = malloc(mlx_tex->height * mlx_tex->width * sizeof(t_rgb));
	if (!img)
		return (NULL);
	bytes_factors[0] = mlx_tex->bytes_per_pixel;
	bytes_factors[1] = mlx_tex->bytes_per_pixel / 4;
	h = 0;
	while (h < mlx_tex->height)
	{
		w = 0;
		while (w < mlx_tex->width)
		{
			assign_pix_val(img, h * mlx_tex->width + w, mlx_tex->pixels,
				bytes_factors);
			w++;
		}
		h++;
	}
	return (img);
}

static void	free_mem(t_obj	*obj)
{
	if (obj->tx.img)
		free(obj->tx.img);
	if (obj->tx.sub_obj)
		free(obj->tx.sub_obj);
	if (obj->tx.mlx_tex_b)
		mlx_delete_texture(obj->tx.mlx_tex_b);
	if (obj->tx.mlx_tex)
		mlx_delete_texture(obj->tx.mlx_tex);
	free(obj);
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
	i = 0 + len_spaces(line);
	obj->tx.mlx_tex = mlx_load_png(read_filename(line, &i));
	if (!obj->tx.mlx_tex)
		return (free_mem(obj), NULL);
	if (typ != BUMP)
		obj->tx.mlx_tex_b = NULL;
	else
	{
		i += len_spaces(line + i);
		obj->tx.mlx_tex_b = mlx_load_png(read_filename(line, &i));
		if (!obj->tx.mlx_tex_b)
			return (free_mem(obj), NULL);
	}
	obj->tx.sub_obj = parse_sphere(line + i);
	if (!obj->tx.sub_obj)
		return (free_mem(obj), NULL);
	obj->tx.img = texture_to_image(obj->tx.mlx_tex);
	if (!obj->tx.img)
		return (free_mem(obj), NULL);
	if (typ != BUMP)
		obj->tx.bump_img = NULL;
	else
	{
		obj->tx.bump_img = texture_to_image(obj->tx.mlx_tex_b);
		if (!obj->tx.bump_img)
			return (free_mem(obj), NULL);
	}
	return (obj);
}
