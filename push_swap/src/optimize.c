/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 09:06:48 by rmander           #+#    #+#             */
/*   Updated: 2021/08/29 20:22:20 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "stack.h"
#include <stdlib.h>

int *indexify(t_data *data, size_t size)
{
	size_t	i;
	int		*copy;

	i = 0;
	if (!alloca_to((void **)&copy, sizeof(int) * size))
		pexit(data, EXIT_FAILURE);
	ft_memcpy(copy, data->values, sizeof(int) * size);
	ft_qsort(copy, 0, size);
	while (i < size)
	{
		data->values[i] = ft_linsearch(copy, size, data->values[i]);
		++i;
	}
	free(copy);
	return (data->values);
}

static int	op_cond(const char *lop, const char *rop)
{
	return ((ft_strcmp(lop, "rra") == 0 && ft_strcmp(rop, "ra") == 0)
			|| (ft_strcmp(lop, "ra") == 0 && ft_strcmp(rop, "rra") == 0)
			|| (ft_strcmp(lop, "rrb") == 0 && ft_strcmp(rop, "rb") == 0)
			|| (ft_strcmp(lop, "pa") == 0 && ft_strcmp(rop, "pb") == 0)
			|| (ft_strcmp(lop, "pb") == 0 && ft_strcmp(rop, "pa") == 0)
			|| (ft_strcmp(lop, "rb") == 0 && ft_strcmp(rop, "rrb") == 0));
}

static	void	cut_op(t_data *data,
					t_list **prev, t_list **curr, t_list **next)
{
	if (*curr == data->ops)
	{
		data->ops = (*next)->next;
		ft_lstdelone(*curr, free);
		ft_lstdelone(*next, free);
		*curr = data->ops;
		*prev = *curr;
	}
	else
	{
		(*prev)->next = (*next)->next;
		ft_lstdelone(*curr, free);
		ft_lstdelone(*next, free);
		*curr = (*prev)->next;
	}
}

void	cutting(t_data *data)
{
	t_list		*curr;
	t_list		*next;
	t_list		*prev;

	curr = data->ops;
	prev = data->ops;
	next = data->ops;
	while (curr)
	{
		next = curr->next;
		if (!next)
			break ;
		if (op_cond((const char *)curr->content,
				(const char *)next->content))
		{
			cut_op(data, &prev, &curr, &next);
			continue ;
		}
		prev = curr;
		curr = next;
	}
}
