/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 08:52:39 by nalebrun          #+#    #+#             */
/*   Updated: 2024/12/17 08:53:10 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

// linear interpolation
static int	intpol(int color_a, int color_b, float t)
{
	t_rgb	a;
	t_rgb	b;
	t_rgb	out;

	a.r = (color_a >> 16) & 0xFF;
	a.g = (color_a >> 8) & 0xFF;
	a.b = color_a & 0xFF;
	b.r = (color_b >> 16) & 0xFF;
	b.g = (color_b >> 8) & 0xFF;
	b.b = color_b & 0xFF;
	out.r = a.r * (1 - t) + b.r * t;
	out.g = a.g * (1 - t) + b.g * t;
	out.b = a.b * (1 - t) + b.b * t;
	return ((out.r << 16) | (out.g << 8) | out.b);
}

void	get_point_color(t_xyz_pt *pt, t_xy_pt *proj, t_map *map)
{
	if (pt->z == 0)
		proj->color = O_COLOR;
	else if (pt->z > 0)
		proj->color = intpol(O_COLOR, POS_COLOR, (float)pt->z / map->z_max);
	else
		proj->color = intpol(O_COLOR, NEG_COLOR, (float)pt->z / map->z_min);
}
