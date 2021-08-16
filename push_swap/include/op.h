/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 04:43:44 by rmander           #+#    #+#             */
/*   Updated: 2021/08/16 05:15:27 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

#include "stack.h"

void	sx(t_data *data, char *cmd);
void	px(t_data *data, char *cmd);	
void	rx(t_data *data, char *cmd);
void	rrx(t_data *data, char *cmd);

#endif
