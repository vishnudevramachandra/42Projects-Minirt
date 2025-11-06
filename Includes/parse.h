/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 09:20:31 by vishnudevra       #+#    #+#             */
/*   Updated: 2025/11/06 09:56:10 by vramacha         ###   ########.fr       */
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

int			set_vector(t_vec *v, const char *s, int *len);
int			set_color(t_rgb *c, const char *s, int *len);
int			set_double(double *d, const char *s, int *len);
int			set_int(int *i, const char *s, int *len);
t_list		*parse_obj(char *line, t_list **objs);
void		print_obj(t_list *objs);

#endif