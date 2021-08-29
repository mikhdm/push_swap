/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 23:08:41 by rmander           #+#    #+#             */
/*   Updated: 2021/08/29 20:22:07 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "op.h"
#include "parse.h"
#include "optimize.h"
#include "stack.h"
#include "utils.h"
#include "error.h"
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

static t_list	*ft_opscopy(t_data *data)
{
	t_list	*new;
	t_list	*old;
	t_list	*node;
	char	*str;

	node = NULL;
	new = NULL;
	str = NULL;
	old = data->ops;
	while (old)
	{
		str = ft_strdup_until((const char *)old->content, '\0');
		if (!str)
			pexit(data, EXIT_FAILURE);
		node = ft_lstnew(str);
		if (!node)
		{
			free(str);
			pexit(data, EXIT_FAILURE);
		}
		ft_lstadd_back(&new, node); 
		old = old->next;
	}
	return (new);
}

static	void	populate(t_data *data, int *values, size_t size)
{
	data->values = values;
	data->a = build(indexify(data, size), size);
	if (!data->a)
		pexit(data, EXIT_FAILURE);
	data->b = build(NULL, size);
	if (!data->b)
		pexit(data, EXIT_FAILURE);
	if (empty(data->a))
		pexit(data, EXIT_SUCCESS);
}

/*
* @brief Runs push_swap with div value.
*
* Runs main machinery with data->values
* applying algorithms with div value on initial
* chunking into stack B. On successful run 
* populates data->ops list with operations.
*
* @param data Global state structure
* @param div Pivot for partition operation in chunking_initial func
* 
* @returns min Updated minimum operations count
*/
static size_t	run(t_data *data, t_list **ops, size_t min, const double div)
{
	size_t	nops;

	push_swap(data, div);
	nops = ft_lstsize(data->ops);
	while (nops--)
		cutting(data);
	nops = ft_lstsize(data->ops);
	if (nops <= min)
	{
		if (*ops)
			ft_lstclear(ops, free);
		*ops = ft_opscopy(data);
		min = nops;
	}
	return (min);
}

static t_list	*opselect(int *values, size_t size)
{
	size_t	i;
	size_t	min;
	t_list	*ops;
	t_data	data;
	const double	div[] = {1.2, 1.5, 1.61, 2, 2.718, 3, 3.14, 3.5,
							3.71, 5.436, 5.71};

	i = 0;
	ops = NULL;
	min = SIZE_T_MAX;
	while (i < (sizeof(div) / sizeof(*div)))
	{
		data = (t_data){.a = NULL, .b = NULL, .ops = NULL, .chunks = NULL,
						.values = NULL};
		populate(&data, values, size);
		min = run(&data, &ops, min, div[i]);
		values = iarrdup(data.values, size);
		if (!values)
			pexit(&data, EXIT_FAILURE);
		cleanup(&data);
		++i;
	}
	if (values)
		free(values);
	return (ops);
}

int main(int argc, char **argv)
{
	t_list	*ops;
	int		*values;

	values = prepare(--argc, ++argv);
	ops = opselect(values, argc);
	ft_lstiter(ops, put_op);
	ft_lstclear(&ops, free);
	return (0);
}
