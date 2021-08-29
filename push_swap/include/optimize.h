/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 09:05:22 by rmander           #+#    #+#             */
/*   Updated: 2021/08/29 09:06:32 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIMIZE_H
# define OPTIMIZE_H

#include "stack.h"

int		*indexify(t_data *data, size_t size);
void	optimize(t_data *data);


#endif

