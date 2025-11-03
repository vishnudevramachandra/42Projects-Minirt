/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:55:21 by majkijew          #+#    #+#             */
/*   Updated: 2025/11/02 15:09:39 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H

# define MINIRT_H
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"

void	erro_msg(char *str, int v);
void	read_from_fd(char *file_name);
int		ft_isspace(char c);
double	atod(char *s);


// stuct 

#endif