/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_math.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:51:39 by majkijew          #+#    #+#             */
/*   Updated: 2025/11/15 15:09:45 by majkijew         ###   ########.fr       */
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
void	add_tuples(t_vec new, t_vec a1, t_vec a2)
{
	new.x = a1.x + a2.x;
	new.y = a1.y + a2.y;
	new.z = a1.z + a2.z;
	new.w = a1.w + a2.w;
}

// substracting tuplets is usefull when it comes to light and shading, when you need to find 
// the vector that points to your light source
void	sub_tuples(t_vec new, t_vec a1, t_vec a2)
{
	new.x = a1.x - a2.x;
	new.y = a1.y - a2.y;
	new.z = a1.z - a2.z;
	new.w = a1.w - a2.w;
}

// imagine u want to see what point lays 3.5 times farther in that direction
void	multi_tuples(t_vec a1, double val)
{
	t_vec	temp;

	temp.x = a1.x * val;
	temp.y = a1.y * val;
	temp.z = a1.z * val;
	temp.w = a1.w * val;
	a1 = temp; 
}

void	div_tuples(t_vec a1, double val)
{
	t_vec	temp;

	temp.x = a1.x / val;
	temp.y = a1.y / val;
	temp.z = a1.z / val;
	temp.w = a1.w / val;
	a1 = temp; 
}
#include <math.h>

// magnitude
//the distance represented by a vector is called its magnitude or lenght, its 
//how far u would travel in straight line if u were to walk from one end of vector to the other
double mag_tuplets(t_vec tup)
{
	double mag;

	// mag += tup.x * tup.x;
	// mag += tup.z * tup.z;
	// mag += tup.y * tup.y;
	mag += pow(tup.x, 2);
	mag += pow(tup.z, 2);
	mag += pow(tup.y, 2);
	return (sqrt(mag));
}

t_vec	normalize(t_vec tup)
{
	t_vec	norm_tup;

	norm_tup.x = tup.x / mag_tuplets(tup);
	norm_tup.y = tup.y / mag_tuplets(tup);
	norm_tup.z = tup.z / mag_tuplets(tup);
	norm_tup.w = tup.w / mag_tuplets(tup);
	return (norm_tup);
}
// vectors with magnitude of 1 are called a unit vectors and u will use them when computing
// the MATRIX when determinin the direction prepend
// int main()
// {
// 	t_vec tup;
// 	double mag;
	
// 	tup.x = 0;
// 	tup.y = 1;
// 	tup.z = 0;

// 	mag = mag_tuplets(tup);
// 	printf("%g\n", mag);
// }