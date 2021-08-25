/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 23:08:41 by rmander           #+#    #+#             */
/*   Updated: 2021/08/25 21:40:27 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "op.h"
#include "stack.h"
#include "utils.h"
#include "error.h"
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

short int duplicated(int *values, size_t size)
{
	size_t		i;
	int			*sorted;
	short int	is;

	sorted = NULL;
	is = FALSE;
	i = 1;
	if (!alloca_to((void **)&sorted, sizeof(int) * size))
	{
		free(values);
		pexit(NULL, EXIT_FAILURE);
	}
	ft_memcpy(sorted, values, sizeof(int) * size);
	sorted = ft_qsort(sorted, 0, size);
	while (i < size)
	{
		if (sorted[i - 1] == sorted[i])
		{
			is = TRUE;
			break ;
		}
		++i;
	}
	free(sorted);
	return (is);
}

int	valid(size_t argc, char **argv)
{
	char	*digit;
	size_t	i;
	ssize_t	value;

	i = 0;
	value = 0;
	while (i < argc)
	{
		digit = argv[i];
		if (*digit == '-' || *digit == '+')
			++digit;
		if (!*digit)
			return (FALSE);
		while(*digit)
		{
			if (!ft_isdigit(*digit))
				return (FALSE);
			++digit;
		}
		value = ft_atoss(argv[i]);
		if ((value > INT_MAX) || (value < INT_MIN))
			return (FALSE);
		++i;
	}
	return (TRUE);
}

int	*parse(size_t argc, char **argv)
{
	int		*data;
	size_t	i;
	
	i = 0;
	data = NULL;
	if (!alloca_to((void **)&data, argc * sizeof(int)))
		return (NULL);
	while (i < argc)
	{
		data[i] = ft_atoi(argv[i]);
		++i;
	}
	return (data);
}

void	printop(void *op)
{
	const char endl = '\n';
	
	write(STDOUT_FILENO, op, ft_strlen_until((const char *)op, '\0'));
	write(STDOUT_FILENO, &endl, 1);
}

int *indexify(t_data *data, int *values, int size)
{
	int		i;
	int		*copy;

	i = 0;
	if (!alloca_to((void **)&copy, sizeof(int) * size))
	{
		free(values);
		pexit(data, EXIT_FAILURE);
	}
	ft_memcpy(copy, values, sizeof(int) * size);
	ft_qsort(copy, 0, size);
	while (i < size)
	{
		values[i] = ft_linsearch(copy, size, values[i]);
		++i;
	}
	free(copy);
	return (values);
}

void	optimize(t_data *data)
{
	t_list		*curr;
	t_list		*next;
	t_list		*prev;
	const char	*lop;
	const char	*rop;

	curr = data->ops;
	prev = data->ops;
	next = data->ops;
	lop = NULL;
	rop = NULL;
	while (curr)
	{
		next = curr->next;
		if (!next)
			break ;
		lop = (const char *)curr->content;
		rop = (const char *)next->content;
		if ((ft_strcmp(lop, "rra") == 0 && ft_strcmp(rop, "ra") == 0)
			|| (ft_strcmp(lop, "ra") == 0 && ft_strcmp(rop, "rra") == 0)
			|| (ft_strcmp(lop, "rrb") == 0 && ft_strcmp(rop, "rb") == 0)
			|| (ft_strcmp(lop, "rb") == 0 && ft_strcmp(rop, "rrb") == 0))
		{
			if (curr == data->ops)
			{
				data->ops = next->next;
				ft_lstdelone(curr, free);
				ft_lstdelone(next, free);
				curr = data->ops;
				prev = curr;
			}
			else
			{
				prev->next = next->next;
				ft_lstdelone(curr, free);
				ft_lstdelone(next, free);
				curr = prev->next;
			}
			continue ;
		}
		prev = curr;
		curr = next;
	}
}

size_t	ft_lstsize(t_list *lst)
{
	size_t	size;

	size = 0;
	while (lst)
	{
		++size;
		lst = lst->next;
	}
	return (size);
}

int main(int argc, char **argv)
{
	t_data	data;
	int		*values;
	int		*indices;
	
	values = NULL;
	indices = NULL;
	data = (t_data){.a = NULL, .b = NULL, .ops = NULL, .chunks = NULL};
	if (!valid(--argc, ++argv))
		pexit(NULL, EXIT_FAILURE);
	values = parse(argc, argv);
	if (!values)
		pexit(NULL, EXIT_FAILURE);
	if (duplicated(values, argc))
		pexit(NULL, EXIT_FAILURE);
	data.a = build(indexify(&data, values, argc), argc);
	free(values);
	if (!data.a)
		pexit(NULL, EXIT_FAILURE);
	data.b = build(NULL, argc);
	if (!data.b)
		pexit(&data, EXIT_FAILURE);

	if (!empty(data.a))
		push_swap(&data);

	optimize(&data);
	ft_lstiter(data.ops, printop);
	cleanup(&data);
	return (0);
}
