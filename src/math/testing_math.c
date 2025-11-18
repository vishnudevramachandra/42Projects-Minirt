/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_math.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:51:39 by majkijew          #+#    #+#             */
/*   Updated: 2025/11/18 15:18:26 by vramacha         ###   ########.fr       */
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
t_tup	add_tuples(t_tup *a, t_tup *b);

// substracting tuplets is usefull when it comes to light and shading, when you need to find 
// the vector that points to your light source
t_tup	sub_tuples(t_tup *a, t_tup *b);

// imagine u want to see what point lays 3.5 times farther in that direction
t_tup	multi_tuple(t_tup *a, double val);

t_tup	div_tuple(t_tup *a, double val);


// magnitude
//the distance represented by a vector is called its magnitude or lenght, its 
//how far u would travel in straight line if u were to walk from one end of vector to the other
double	magnitude(t_tup *a);

t_tup	normalize(t_tup *a);

// vectors with magnitude of 1 are called a unit vectors and u will use them when computing
// the MATRIX when determinin the direction prepend
int main()
{
	t_tup tup = {1, 2, 2};

	printf("Magnitude: (%g,%g,%g,%g) is %g\n", tup.x, tup.y, tup.z, tup.w, magnitude(&tup));
	t_tup tmp = add_tuples(&tup, &tup);
	printf("Addition: (%g,%g,%g,%g)\n", tmp.x, tmp.y, tmp.z, tmp.w);
	tmp = div_tuple(&tup, 2);
	printf("Division: (%g,%g,%g,%g)\n", tmp.x, tmp.y, tmp.z, tmp.w);
	tmp = normalize(&tup);
	printf("Normalize: (%g,%g,%g,%g)\n", tmp.x, tmp.y, tmp.z, tmp.w);
}