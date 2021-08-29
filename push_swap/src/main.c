/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 23:08:41 by rmander           #+#    #+#             */
/*   Updated: 2021/08/29 09:27:27 by rmander          ###   ########.fr       */
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
#include <stdio.h>

static void	print_op(void *op)
{
	write(STDOUT_FILENO, op, ft_strlen_until((const char *)op, '\0'));
	write(STDOUT_FILENO, "\n", 1);
}

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

void	populate(t_data *data, int *values, size_t size)
{
	data->values = values;
	data->a = build(indexify(data, size), size);
	if (!data->a)
		pexit(data, EXIT_FAILURE);
	data->b = build(NULL, size);
	if (!data->b)
		pexit(data, EXIT_FAILURE);
}

/* @brief Runs push_swap with div value.
 *
 * Runs main machinery with data->values
 * applying algorithms with div value on initial
 * chunking into stack B. On successful run 
 * populates data->ops list with operations.
 *
 * @param data Global state structure
 * @param div Pivot for partition operation in chunking_initial func
 * 
 * @returns Nothing
 */
void	run(t_data *data, const double div)
{
	size_t	nops;
	push_swap(data, div);
	nops = ft_lstsize(data->ops);
	while (nops--)
		optimize(data);
}

int main(int argc, char **argv)
{
	t_data	data;
	t_list	*ops;
	int		*values;
	size_t	min;
	size_t	runs;
	size_t	nops;
	size_t	i;
	const double	div[] = {1.5, 1.61, 2, 2.718, 3, 3.14};

	i = 0;
	min = SIZE_T_MAX;
	runs = sizeof(div) / sizeof(*div);
	values = prepare(--argc, ++argv);
	ops = NULL;

	while (i < runs)
	{
		data = (t_data){.a = NULL, .b = NULL, .ops = NULL, .chunks = NULL,
						.values = NULL};
		populate(&data, values, argc);
		if (empty(data.a))
		{
			cleanup(&data);
			return (0);
		}
		run(&data, div[i]);
		nops = ft_lstsize(data.ops);
		if (nops <= min)
		{
			if (ops)
				ft_lstclear(&ops, free);
			ops = ft_opscopy(&data);
			min = nops;
		}
		values = iarrdup(data.values, argc);
		if (!values)
			pexit(&data, EXIT_FAILURE);
		cleanup(&data);
		++i;
	}
	free(values);
	ft_lstiter(ops, print_op);
	ft_lstclear(&ops, free);
	return (0);
}
