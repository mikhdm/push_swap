/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 23:08:41 by rmander           #+#    #+#             */
/*   Updated: 2021/08/24 00:45:27 by rmander          ###   ########.fr       */
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

int main(int argc, char **argv)
{
	t_data	data;
	int		*values;
	
	values = NULL;
	data = (t_data){.a = NULL, .b = NULL, .ops = NULL,
					.chunks = NULL};
	if (!valid(--argc, ++argv))
		pexit(NULL, EXIT_FAILURE);
	values = parse(argc, argv);
	if (!values)
		pexit(NULL, EXIT_FAILURE);
	if (duplicated(values, argc))
		pexit(NULL, EXIT_FAILURE);
	data.a = build(values, argc);
	free(values);
	if (!data.a)
		pexit(NULL, EXIT_FAILURE);
	data.b = build(NULL, argc);
	if (!data.b)
		pexit(&data, EXIT_FAILURE);

	/* printf("%sSTACK A:%s\n", color, NC); */
	/* debug(data.a); */

	if (!empty(data.a))
		push_swap(&data);

	/* printf("%sSTACK A:%s\n", color, NC); */
	/* debug(data.a); */

	ft_lstiter(data.ops, printop);
	cleanup(&data);
	return (0);
}
