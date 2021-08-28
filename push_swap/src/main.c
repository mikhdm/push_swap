/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 23:08:41 by rmander           #+#    #+#             */
/*   Updated: 2021/08/29 00:57:43 by rmander          ###   ########.fr       */
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
			|| (ft_strcmp(lop, "pa") == 0 && ft_strcmp(rop, "pb") == 0)
			|| (ft_strcmp(lop, "pb") == 0 && ft_strcmp(rop, "pa") == 0)
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

t_list	*ft_opscopy(t_data *data)
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

int	*prepare(int argc, char **argv)
{
	int *values;

	values = NULL;
	if (!valid(--argc, ++argv))
		pexit(NULL, EXIT_FAILURE);
	values = parse(argc, argv);
	if (!values)
		pexit(NULL, EXIT_FAILURE);
	if (duplicated(values, argc))
	{
		free(values);
		pexit(NULL, EXIT_FAILURE);
	}
	return (values);
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


int main(int argc, char **argv)
{
	t_data	data;
	size_t	nops;
	int		*values;
	size_t	min;
	size_t	div_sz;
	size_t	i;
	t_list	*ops;
	const double	div[] = {1.61, 2, 2.718, 3, 3.14};
	values = prepare(argc, argv);

	i = 0;
	min = SIZE_T_MAX;
	div_sz = sizeof(div) / sizeof(*div);
	ops = NULL;
	while (i < div_sz)
	{
		data = (t_data){.a = NULL, .b = NULL, .ops = NULL, .chunks = NULL,
						.values = NULL};
		populate(&data, values, argc);
		if (empty(data.a))
		{
			cleanup(&data);
			break ;
		}
		push_swap(&data, div[i]);
		/* operations optimizations */
		nops = ft_lstsize(data.ops);
		while (nops--)
			optimize(&data);
		nops = ft_lstsize(data.ops);
		if (nops <= min)
		{
			ops = ft_opscopy(&data);
			min = nops;
		}
		values = NULL;
		if (!alloca_to((void **)&values, sizeof(int) * argc))
			pexit(&data, EXIT_FAILURE);
		ft_memcpy(values, data.values, sizeof(int) * argc);
		cleanup(&data);
		++i;
	}
	if (values)
		free(values);
	if (ops)
	{
		ft_lstiter(ops, printop);
		ft_lstclear(&ops, free);
	}
	return (0);
}
