/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 07:41:32 by rmander           #+#    #+#             */
/*   Updated: 2021/08/30 07:51:25 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "utils.h"
#include "stack.h"
#include "get_next_line.h"
#include <stdlib.h>

static int	op_valid(const char *cmd)
{
	size_t	i;
	const char *ops[] = {"sa", "sb", "ss", "pa", "pb",
						"ra", "rb", "rr", "rra", "rrb", "rrr"};

	if (!cmd)
		return (FALSE);
	i = 0;
	while (i < (sizeof(ops) / sizeof(*ops)))
		if (ft_strcmp(cmd, ops[i++]) == 0)
			return (TRUE);
	return (FALSE);
}

static t_list *op_add(t_data *data, t_list *ops, char *cmd)
{
	t_list	*node;
	
	node = NULL;
	if (!op_valid(cmd))
	{
		if (cmd)
			free(cmd);
		pexit(data, EXIT_FAILURE);
	}
	node = ft_lstnew(cmd);
	if (!node)
	{
		if (cmd)
			free(cmd);
		pexit(data, EXIT_FAILURE);
	}
	ft_lstadd_back(&ops, node);
	return (ops);
}

t_list	*ops_read(t_data *data)
{
	t_list	*ops;
	char	*cmd;
	int		state;

	ops = NULL;
	while (TRUE)
	{
		cmd = NULL;
		state = get_next_line(STDIN_FILENO, &cmd);
		if (state == SIG_ERROR)
			pexit(data, EXIT_FAILURE);
		if (state == SIG_EOF)
			break ;
		ops = op_add(data, ops, cmd);
	}
	if (op_valid(cmd))
	{
		if (cmd)
			free(cmd);
		pexit(data, EXIT_FAILURE);
	}
	free(cmd);
	return (ops);
}
