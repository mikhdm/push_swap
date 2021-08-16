/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 23:08:41 by rmander           #+#    #+#             */
/*   Updated: 2021/08/16 03:06:47 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"
#include "utils.h"
#include "error.h"
#include <limits.h>
#include <stdlib.h>
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

void	debug(t_stack *stack)
{
	size_t	i;

	i = stack->capacity;
	printf("\n-- DEBUG --\n\n");
	while (i > 0)
	{
		if (i > stack->size)
			printf("|%6s|\n", "");
		else
			printf("|%6d| (%p)\n", stack->data[i - 1], &stack->data[i - 1]);
		--i;
	}
	printf("capacity: %zu\n", stack->capacity);
	printf("size: %zu\n", stack->size);
	if (stack->top)
		printf("top: %d (%p)\n", *stack->top, stack->top);
	else
		printf("top: null\n");
	printf("\n-- END --\n\n");
}

int main(int argc, char **argv)
{
	t_data	data;
	int		*values;
	
	values = NULL;
	data = (t_data){.a = NULL, .b = NULL, .ops = NULL};
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
	
	debug(data.a);

	printf("popped: %d\n", *pop_back(data.a));
	debug(data.a);

	printf("popped: %d\n", *pop_back(data.a));
	debug(data.a);

	printf("popped: %d\n", *pop_back(data.a));
	debug(data.a);

	push_front(data.a, 10000);
	push_front(data.a, 20000);
	push_front(data.a, 30000);

	debug(data.a);


	/* push_back(data.a, 100); */

	/* debug(data.a); */

	/* push_back(data.a, 200); */

	/* debug(data.a); */

	/* push_back(data.a, 0); */

	/* debug(data.a); */

	cleanup(&data);
	return (0);
}
