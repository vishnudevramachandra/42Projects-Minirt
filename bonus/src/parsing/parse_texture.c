/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:22:56 by vramacha          #+#    #+#             */
/*   Updated: 2026/01/31 15:21:55 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "minirt_bonus.h"

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

void	free_tx(t_obj	*obj)
{
	if (obj->tx.bump_img)
		free(obj->tx.bump_img);
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

static int	load_mlx_texture(mlx_texture_t **tex, char *line, int *i)
{
	char	*filename;

	*i += len_spaces(line + *i);
	filename = read_filename(line, i);
	if (!filename)
		return (0);
	*tex = mlx_load_png(filename);
	free(filename);
	if (!*tex)
		return (0);
	return (1);
}

t_obj	*parse_texture(char *line, t_tex_type typ)
{
	int		i;
	t_obj	*obj;

	obj = create_and_init_tex_obj(typ);
	if (!obj)
		return (NULL);
	i = 0;
	if (!load_mlx_texture(&obj->tx.mlx_tex, line, &i))
		return (free_tx(obj), NULL);
	if (typ == BUMP)
		if (!load_mlx_texture(&obj->tx.mlx_tex_b, line, &i))
			return (free_tx(obj), NULL);
	obj->tx.sub_obj = parse_sphere(line + i);
	if (!obj->tx.sub_obj)
		return (free_tx(obj), NULL);
	obj->tx.img = texture_to_image(obj->tx.mlx_tex);
	if (!obj->tx.img)
		return (free_tx(obj), NULL);
	if (typ == BUMP)
	{
		obj->tx.bump_img = texture_to_image(obj->tx.mlx_tex_b);
		if (!obj->tx.bump_img)
			return (free_tx(obj), NULL);
	}
	return (obj);
}
