/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 20:35:54 by vramacha          #+#    #+#             */
/*   Updated: 2026/01/31 14:17:43 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minirt.h"

static int	compare_t(double t1, double t2)
{
	if (t1 < t2)
		return (1);
	else
		return (0);
}

static int	is_lesser_helper(t_inter *a, double n)
{
	if (0 < a->t0)
		return (compare_t(a->t0, n));
	else
		return (compare_t(a->t1, n));
}

static int	is_lesser(t_inter *a, t_inter *b)
{
	if (0 < b->t0)
		return (is_lesser_helper(a, b->t0));
	else
		return (is_lesser_helper(a, b->t1));
}

void	insert_intersection(t_inter **list, t_inter *new, t_obj *obj, double *t)
{
	t_inter	*cur;

	new->t0 = t[0];
	new->t1 = t[1];
	new->obj = obj;
	if (*list == NULL || is_lesser(new, *list))
	{
		new->next = *list;
		*list = new;
		return ;
	}
	cur = *list;
	while (cur->next && is_lesser(cur->next, new))
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
