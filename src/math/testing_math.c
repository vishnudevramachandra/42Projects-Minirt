/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_math.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:51:39 by majkijew          #+#    #+#             */
/*   Updated: 2025/11/19 10:02:38 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "../../Includes/minirt.h"

// punk to na przyklad pozycja kamery
// vector bylby naprzyklad o pokazania w ktorym kierunku swieci swiatlo jak pada
//pozycja punktu w promeniu 

//Vector stors the direction and distance ||| point does not its just a point ..
//the distance represented by a vectoir is called the magnitude, or lenght
//its how far you would travel in a straight line if u were to walk from one end of the vector to the other


//comperring vectors and point but idk what for

double	ft_abs(double num)
{
	if (num < 0)
		return (-num);
	return (num);
}

// addint two tuples
//imagin that u have a point (3,-2,5,1) and a vector (-2, 3,1,0) and u want to know ehre you woult be if 
//u followed thr vector from that point the answear comes via adding - adding the two tuples toghether
// void	add_tuples(double *new_tuple, double *tuple1, double *tuple2)
// {
// 	int	i = 0;
// 	// dobra czyli mamy jakby dwa ciagi liczb x y z i jesli bedziemy sie trzymac tej 
// 	// ksaizki to mamy tez w czyli 1 jesli point 0 jesli vector
	
// 	while (i < 4)
// 	{
// 		new_tuple[i] = tuple1[i] + tuple2[i];
// 		i++;
// 	}
// 	new_tuple[i] = '\0';
// }

// addint two tuples
//imagin that u have a point (3,-2,5,1) and a vector (-2, 3,1,0) and u want to know ehre you woult be if 
//u followed thr vector from that point the answear comes via adding - adding the two tuples toghether
void		add_tuples(t_tup res, t_tup a, t_tup b);

// substracting tuplets is usefull when it comes to light and shading, when you need to find 
// the vector that points to your light source
void		sub_tuples(t_tup res, t_tup a, t_tup b);

// imagine u want to see what point lays 3.5 times farther in that direction
void		multi_tuple(t_tup res, t_tup a, double val);

void		div_tuple(t_tup res, t_tup a, double val);


// magnitude
//the distance represented by a vector is called its magnitude or lenght, its 
//how far u would travel in straight line if u were to walk from one end of vector to the other
double	magnitude(t_tup a);

void		normalize(t_tup res, t_tup a);

// vectors with magnitude of 1 are called a unit vectors and u will use them when computing
// the MATRIX when determinin the direction prepend
int main()
{
	t_tup tup = {1, 2, 2, 0};

	printf("sqrt: %g\n", sqrt(tup[0] * tup[0] + tup[1] * tup[1] + tup[2] * tup[2] + tup[3] * tup[3]));
	printf("dot-prod: %g\n", dot_prod(tup, tup));
	printf("Magnitude: (%g,%g,%g,%g) is %g\n", tup[0], tup[1], tup[2], tup[3], magnitude(tup));
	t_tup tmp;
	add_tuples(tmp, tup, tup);
	printf("Addition: (%g,%g,%g,%g)\n", tup[0], tup[1], tup[2], tup[3]);
	div_tuple(tmp, tup, 2);
	printf("Division: (%g,%g,%g,%g)\n", tup[0], tup[1], tup[2], tup[3]);
	normalize(tup, tup);
	printf("Normalize: (%g,%g,%g,%g)\n", tup[0], tup[1], tup[2], tup[3]);
	cross_prod(tmp, tup, tup);
	printf("Cross-product: (%g,%g,%g,%g)\n", tmp[0], tmp[1], tmp[2], tmp[3]);
	
	mat4    a = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 6}, {5, 4, 3, 2}};
	mat4    b = {{-2, 1, 2, 3}, {3, 2, 1, -1}, {4, 3, 6, 5}, {1, 2, 7, 8}};
    mat4    res = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
	multi_mat_mat(res, a, b);
	printf("MMM: ((%g,%g,%g,%g),(%g,%g,%g,%g),(%g,%g,%g,%g),(%g,%g,%g,%g))\n",
		res[0][0],res[0][1],res[0][2],res[0][3],
		res[1][0],res[1][1],res[1][2],res[1][3],
		res[2][0],res[2][1],res[2][2],res[2][3],
		res[3][0],res[3][1],res[3][2],res[3][3]);
	mat4	c = {{1, 2, 3, 4}, {2, 4, 4, 2}, {8, 6, 4, 1}, {0, 0, 0, 1}};
	t_tup	v = {1, 2, 3, 1};
	multi_mat_tuple(tup, c, v);
	printf("Matrix-tuple mul: (%g,%g,%g,%g)\n", tup[0], tup[1], tup[2], tup[3]);
	transpose_mat(res);
	printf("transpose: ((%g,%g,%g,%g),(%g,%g,%g,%g),(%g,%g,%g,%g),(%g,%g,%g,%g))\n",
		res[0][0],res[0][1],res[0][2],res[0][3],
		res[1][0],res[1][1],res[1][2],res[1][3],
		res[2][0],res[2][1],res[2][2],res[2][3],
		res[3][0],res[3][1],res[3][2],res[3][3]);
	printf("Matrix equality {yes[1]/no[0]}: %i\n", is_equal_mat(res, res));
}
