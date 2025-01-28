/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:33:43 by wkornato          #+#    #+#             */
/*   Updated: 2025/01/28 21:51:56 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>

typedef enum e_anim_type
{
	XYSINE,
	XSINE,
	YSINE,
	WATER,
	RIPPLE,
	WIND,
	SHAKY
}				t_anim_type;

typedef struct s_anim_info
{
	t_anim_type	type;
	int			iter;
	int			x;
	int			y;
}				t_anim_info;
