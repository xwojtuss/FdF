/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 22:52:04 by wkornato          #+#    #+#             */
/*   Updated: 2025/01/24 12:22:53 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

typedef	struct s_v3i
{
	int		x;
	int		y;
	int		z;
}			t_v3i;

t_v3i		add_v3i(t_v3i v1, t_v3i v2);

#endif
