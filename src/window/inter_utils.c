/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 20:35:54 by vramacha          #+#    #+#             */
/*   Updated: 2026/01/26 20:36:04 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minirt.h"

void	insert_intersection(t_inter **list, t_inter *new, t_obj *obj, double t)
{
	t_inter	*cur;

	if (!new)
	{
		//has to be handled;
	}
	new->t = t;
	new->obj = obj;
	if (*list == NULL || new->t < (*list)->t)
	{
		new->next = *list;
		*list = new;
		return ;
	}
	cur = *list;
	while (cur->next && cur->next->t < new->t)
		cur = cur->next;
	new->next = cur->next;
	cur->next = new;
}

void	free_list(t_inter *i)
{
	t_inter	*temp;

	while (i)
	{
		temp = i->next;
		free(i);
		i = temp;
	}
}
