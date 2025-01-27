/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:46:07 by wkornato          #+#    #+#             */
/*   Updated: 2025/01/27 13:48:01 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	copy_point(t_point srcs, t_point *dest)
{
	dest->x_pos = srcs.x_pos;
	dest->y_pos = srcs.y_pos;
	dest->z_pos = srcs.z_pos;
	dest->color = srcs.color;
}
