/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 22:52:04 by wkornato          #+#    #+#             */
/*   Updated: 2025/01/14 22:39:59 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

typedef	struct s_v3
{
	float	x;
	float	y;
	float	z;
	int		padding;//padding for casting
}			t_v3;

#endif
