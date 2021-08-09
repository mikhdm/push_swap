/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 23:08:41 by rmander           #+#    #+#             */
/*   Updated: 2021/08/09 05:55:08 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"
#include "utils.h"
#include "error.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

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

void	show(t_stack *stack)
{
	size_t	i;

	i = 0;
	printf("----\n");
	while (i < stack->size)
		printf("%4d\n", stack->data[stack->size - i++ - 1]);
	printf("----\n");
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
	show(data.a);
	cleanup(&data);
	return (0);
}
