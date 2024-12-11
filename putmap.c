/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:34:56 by nalebrun          #+#    #+#             */
/*   Updated: 2024/12/10 17:34:58 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_xy_pt	proj_iso_pt(t_xyz_pt *pt, float zoom)
{
	t_xy_pt	proj_pt;
	float	theta;
	float	z;

	theta = to_rad(35.61);
	proj_pt.x = zoom * (pt->x - pt->y) * cos(theta);
	if (AMP != 0)
		z = pt->z * (AMP + 10) / 100;
	else
		z = pt->z * (AMP) / 100;
	proj_pt.y = zoom * ((pt->x + pt->y) * sin(theta) - z);
	return (proj_pt);
}

static void	shift_to_center(t_xy_pt *pt, t_xy_pt offset)
{
	pt->x += offset.x;
	pt->y += offset.y;
}

void	draw_line_axis(t_img *img, t_xyz_pt *ref, t_map *map, int color)
{
	int		i;
	t_xy_pt	proj_from;
	t_xy_pt	proj_to;

	i = 0;
	while (map->cld[i])
	{
		if (map->cld[i]->y == ref->y + 1 && ref->x == map->cld[i]->x)
		{
			proj_from = proj_iso_pt(ref, map->zoom);
			proj_to = proj_iso_pt(map->cld[i], map->zoom);
			shift_to_center(&proj_from, map->offset);
			shift_to_center(&proj_to, map->offset);
			draw_line(img, proj_from, proj_to, color);
		}
		if (map->cld[i]->x == ref->x + 1 && ref->y == map->cld[i]->y)
		{
			proj_from = proj_iso_pt(ref, map->zoom);
			proj_to = proj_iso_pt(map->cld[i], map->zoom);
			shift_to_center(&proj_from, map->offset);
			shift_to_center(&proj_to, map->offset);
			draw_line(img, proj_from, proj_to, color);
		}
		i++;
	}
}

void	proj_cloud_to_img(t_map *map, t_img *img, int color)
{
	int	i;

	i = 0;
	while (map->cld[i])
	{
		draw_line_axis(img, map->cld[i], map, color);
		i++;
	}
}
