/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 11:45:00 by vramacha          #+#    #+#             */
/*   Updated: 2025/12/01 14:40:56 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "../../libft/libft.h"

// return a static address that serves as the root address of garbage collector.
static void	**gc_root(void)
{
	static void	*ptr;

	return (&ptr);
}

// add the given pointer to garbage collector list.
static t_list	*gc_add(void *ptr)
{
	t_list	*new;

	new = ft_lstnew(ptr);
	if (!new)
		return (NULL);
	ft_lstadd_back((t_list **)gc_root(), new);
	return (new);
}

// malloc bytes of 'size' and before returning a pointer to it, add it to GC.
void	*gc_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr || !gc_add(ptr))
		return (NULL);
	return (ptr);
}

// free all memory on Garbage collector.
void	gc_destroy(void)
{
	ft_lstclear((t_list **)gc_root(), free);
}

#include <stdio.h>

int	main(void)
{
	printf("%p\n", gc_root());
	printf("%p\n", *(void **)gc_root());
	char	*str = gc_malloc(4);
	str[0] = 'G'; str[1] = 'C'; str[3] = 0;
	printf("%s\n", str);
	int	*arr = gc_malloc(3 * sizeof(int));
	arr[0] = 200; arr[2] = -200;
	printf("%i, %i\n", arr[0], arr[2]);
	gc_destroy();
}
