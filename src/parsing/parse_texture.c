/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:22:56 by vramacha          #+#    #+#             */
/*   Updated: 2026/01/29 17:57:38 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "minirt.h"

static char	*read_filename(char *line, int *i)
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

static t_rgb	*texture_to_image(t_texture *tx)
{
	t_rgb		*img;
	uint32_t	h;
	uint32_t	w;
	uint8_t		bytes_factors[2];

	img = malloc(tx->mlx_tex->height * tx->mlx_tex->width * sizeof(t_rgb));
	if (!img)
		return (NULL);
	bytes_factors[0] = tx->mlx_tex->bytes_per_pixel;
	bytes_factors[1] = tx->mlx_tex->bytes_per_pixel / 4;
	h = 0;
	while (h < tx->mlx_tex->height)
	{
		w = 0;
		while (w < tx->mlx_tex->width)
		{
			assign_pix_val(img, h * tx->mlx_tex->width + w, tx->mlx_tex->pixels,
				bytes_factors);
			w++;
		}
		h++;
	}
	return (img);
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
	obj->tx.sub_obj = parse_sphere(line + i);
	if (!obj->tx.sub_obj)
	{
		mlx_delete_texture(obj->tx.mlx_tex);
		free(obj);
		return (NULL);
	}
	obj->tx.img = texture_to_image(&obj->tx);
	if (!obj->tx.img)
	{
		free(obj->tx.sub_obj);
		mlx_delete_texture(obj->tx.mlx_tex);
		free(obj);
		return (NULL);
	}
	return (obj);
}
