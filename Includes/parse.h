/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 09:20:31 by vishnudevra       #+#    #+#             */
/*   Updated: 2026/01/30 22:22:38 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minirt.h"

typedef enum e_datatype
{
	DOUBLE,
	INT,
}	t_dataype;

int		set_tuple(t_tup v, const char *s, int *len, double w);
int		set_color(t_rgb *c, const char *s, int *len);
int		set_double(double *d, const char *s, int *len);
int		set_int(int *i, const char *s, int *len);
t_obj	*parse_sphere(char *line);
t_obj	*parse_texture(char *line, t_tex_type typ);
t_list	*parse_obj(char *line, t_list **objs);
void	print_obj(t_list *objs);
int		set_pattern(t_material *mt, char *line, int *len);
char	*read_filename(char *line, int *i);
t_obj	*create_and_init_tex_obj(t_tex_type typ);
void	free_tx(t_obj	*obj);

#endif