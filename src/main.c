/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:42:07 by majkijew          #+#    #+#             */
/*   Updated: 2025/10/31 15:19:08 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	// first we would if we have 2 argumenst 
	// the name of the program and file.rt 

	// the we check if the rt exists

	// first we look for the specifires A | C | L (sp, pl, cy);

	// so we have t ocheck if the a c l is in the right range if no exit errormsg 

	// the we checkl wich kind of figure we have 

	// this is the basci parsing^
	
	// basci math functions 

	printf("%lf\n", atod("       0.2"));
	printf("%lf\n", atod("225.225,225"));
	printf("%lf\n", atod("0.0,0.0,20.6"));
}
