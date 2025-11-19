/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_math.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:51:39 by majkijew          #+#    #+#             */
/*   Updated: 2025/11/19 16:13:12 by vramacha         ###   ########.fr       */
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
	
	// ---------------matrix operations------------------
	mat4    a = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 6}, {5, 4, 3, 2}};
	mat4    b = {{-2, 1, 2, 3}, {3, 2, 1, -1}, {4, 3, 6, 5}, {1, 2, 7, 8}};
    mat4    res = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
	multi_mat_mat(res, a, b);	// ((20,22,50,48),(44,54,114,108),(40,58,110,102),(16,26,46,42))
	printf("MMM: ((%g,%g,%g,%g),(%g,%g,%g,%g),(%g,%g,%g,%g),(%g,%g,%g,%g))\n",
		res[0][0],res[0][1],res[0][2],res[0][3],
		res[1][0],res[1][1],res[1][2],res[1][3],
		res[2][0],res[2][1],res[2][2],res[2][3],
		res[3][0],res[3][1],res[3][2],res[3][3]);
	mat4	c = {{1, 2, 3, 4}, {2, 4, 4, 2}, {8, 6, 4, 1}, {0, 0, 0, 1}};
	t_tup	v = {1, 2, 3, 1};
	multi_mat_tuple(tup, c, v);	// (18, 24, 33,1)
	printf("Matrix-tuple mul: (%g,%g,%g,%g)\n", tup[0], tup[1], tup[2], tup[3]);
	transpose_mat(res);	// ((20,44,40,16),(22,54,58,26),(50,114,110,46),(48,108,102,42))
	printf("transpose: ((%g,%g,%g,%g),(%g,%g,%g,%g),(%g,%g,%g,%g),(%g,%g,%g,%g))\n",
		res[0][0],res[0][1],res[0][2],res[0][3],
		res[1][0],res[1][1],res[1][2],res[1][3],
		res[2][0],res[2][1],res[2][2],res[2][3],
		res[3][0],res[3][1],res[3][2],res[3][3]);
	printf("Matrix equality {yes[1]/no[0]}: %i\n", is_equal_mat(res, res));
	
	// ---------------Translation, scaling, rotation, shearing------------------
	mat4	t;
	mat4	*bla;
	double	d[3] = {5, -3, 2};
	bla = translation_mat(t, d);	// ((1,0,0,5),(0,1,0,-3),(0,0,1,2),(0,0,0,1))
	printf("transpose: ((%g,%g,%g,%g),(%g,%g,%g,%g),(%g,%g,%g,%g),(%g,%g,%g,%g))\n",
		t[0][0],t[0][1],t[0][2],t[0][3],
		t[1][0],t[1][1],t[1][2],t[1][3],
		t[2][0],t[2][1],t[2][2],t[2][3],
		t[3][0],t[3][1],t[3][2],t[3][3]);
	printf("[0][3]: %g\n", (*bla)[0][3]);
	t_tup	vec = {-3, 4, 5, 0};
	multi_mat_tuple(tup, *bla, vec); // (-3, 4, 5, 0)
	printf("Transl of vec: (%g,%g,%g,%g)\n", tup[0], tup[1], tup[2], tup[3]);
	t_tup	pt = {-3, 4, 5, 1};
	multi_mat_tuple(tup, *bla, pt);	// (2, 1, 7, 1)
	printf("Transl of point: (%g,%g,%g,%g)\n", tup[0], tup[1], tup[2], tup[3]);
	d[0] = 2; d[1] = 3; d[2] = 4;
	mat4	s;
	scaling_mat(s, d);
	pt[0] = -4; pt[1] = 8; pt[2] = 8;
	multi_mat_tuple(tup, s, pt);	// (-8, 18, 32, 1)
	printf("Transl of point: (%g,%g,%g,%g)\n", tup[0], tup[1], tup[2], tup[3]);
	mat4	r;
	d[0] = 0; d[1] = 0; d[2] = M_PI / 4;
	rotation_mat(r, d);
	printf("rot-mat: ((%g,%g,%g,%g),(%g,%g,%g,%g),(%g,%g,%g,%g),(%g,%g,%g,%g))\n",
		r[0][0],r[0][1],r[0][2],r[0][3],
		r[1][0],r[1][1],r[1][2],r[1][3],
		r[2][0],r[2][1],r[2][2],r[2][3],
		r[3][0],r[3][1],r[3][2],r[3][3]);
	pt[0] = 0; pt[1] = 1; pt[2] = 0;
	multi_mat_tuple(tup, r, pt);	// (0, 0.707107, 0.707107, 1)
	printf("Rotation of point: (%g,%g,%g,%g)\n", tup[0], tup[1], tup[2], tup[3]);
	mat4	shr;
	double	w[6] = {1, -1, 2, -2, 3, -3};
	shearing_mat(shr, w);
	printf("rot-mat: ((%g,%g,%g,%g),(%g,%g,%g,%g),(%g,%g,%g,%g),(%g,%g,%g,%g))\n",
		shr[0][0],shr[0][1],shr[0][2],shr[0][3],
		shr[1][0],shr[1][1],shr[1][2],shr[1][3],
		shr[2][0],shr[2][1],shr[2][2],shr[2][3],
		shr[3][0],shr[3][1],shr[3][2],shr[3][3]);
}
