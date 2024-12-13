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

#include "../fdf.h"

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

void	draw_line_axis(t_img *img, int i, t_map *map, int color)
{
	t_xy_pt	proj_from;
	t_xy_pt	proj_to;

	proj_from = proj_iso_pt(map->cld[i], map->zoom);
	shift_to_center(&proj_from, map->offset);
	if (i % map->size.x != map->size.x - 1)
	{
		proj_to = proj_iso_pt(map->cld[i + 1], map->zoom);
		shift_to_center(&proj_to, map->offset);
		draw_line(img, proj_from, proj_to, color);
	}
	if (!(i + map->size.x >= (map->size.x * map->size.y)))
	{
		proj_to = proj_iso_pt(map->cld[i + map->size.x], map->zoom);
		shift_to_center(&proj_to, map->offset);
		draw_line(img, proj_from, proj_to, color);
	}
}

void	proj_cloud_to_img(t_map *map, t_img *img, int color)
{
	int	i;

	i = 0;
	while (map->cld[i])
	{
		draw_line_axis(img, i, map, color);
		i++;
	}
}
