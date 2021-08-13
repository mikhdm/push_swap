/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 23:08:41 by rmander           #+#    #+#             */
/*   Updated: 2021/08/13 23:16:36 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"
#include "utils.h"
#include "error.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

/* void	sort(int *values, size_t size) */
/* { */
/* 	/1* TODO *1/ */
/* } */

/* short int duplicated(int *values, size_t size) */
/* { */
/* 	size_t	i; */
/* 	int		*sorted; */
	
/* 	i = 0; */
/* 	/1* TODO check neigbours in the sorted array (a - b) == 0) *1/ */
/* 	return (FALSE); */
/* } */

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

	i = 0;
	printf("\n-- DEBUG --\n\n");
	while (i < stack->size)
	{
		printf("|%4d| (%p)\n",
				stack->data[stack->size - i - 1],
				&stack->data[stack->size - i - 1]);
		++i;
	}
	printf("size: %zu\n", stack->size);
	if (stack->top)
		printf("top: %d (%p)\n", *stack->top, stack->top);
	else
		printf("top: null\n");
	if (stack->bottom)
		printf("bottom: %d (%p)\n", *stack->bottom, stack->bottom);
	else
		printf("bottom: null\n");

	printf("\n-- END --\n");
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
	data.a = build(values, argc);
	free(values);
	if (!data.a)
		pexit(NULL, EXIT_FAILURE);
	data.b = build(NULL, argc);
	if (!data.b)
		pexit(&data, EXIT_FAILURE);

	debug(data.a);

	printf("popped: %d\n", *pop(data.a));
	debug(data.a);

	printf("popped: %d\n", *pop(data.a));
	debug(data.a);

	printf("popped: %d\n", *pop(data.a));
	debug(data.a);

	push(data.a, 100);

	cleanup(&data);
	return (0);
}
