/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:40:53 by nalebrun          #+#    #+#             */
/*   Updated: 2024/12/11 12:41:26 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slop.h"

static int	get_direction(int pt, int pt_)
{
	if (pt < pt_)
		return (1);
	else
		return (-1);
}

// em = error margin
static void	shallow_slope(t_img *img, t_xy_pt d, t_slop_pts sp, int color)
{
	int	sx;
	int	sy;
	int	em;

	sx = get_direction(sp.from.x, sp.to.x);
	sy = get_direction(sp.from.y, sp.to.y);
	em = (int)(d.x / 2);
	while (sp.from.x != sp.to.x)
	{
		mlx_put_px(img, sp.from.x, sp.from.y, color);
		sp.from.x += sx;
		em -= d.y;
		if (em < 0)
		{
			sp.from.y += sy;
			em += d.x;
		}
	}
}

static void	steep_slope(t_img *img, t_xy_pt d, t_slop_pts sp, int color)
{
	int	sx;
	int	sy;
	int	em;

	sx = get_direction(sp.from.x, sp.to.x);
	sy = get_direction(sp.from.y, sp.to.y);
	em = (int)(d.y / 2);
	while (sp.from.y != sp.to.y)
	{
		mlx_put_px(img, sp.from.x, sp.from.y, color);
		sp.from.y += sy;
		em -= d.x;
		if (em < 0)
		{
			sp.from.x += sx;
			em += d.y;
		}
	}
}

void	draw_line(t_img *img, t_xy_pt from, t_xy_pt to, int color)
{
	t_xy_pt		d;
	t_slop_pts	sp;

	sp.from = from;
	sp.to = to;
	d.x = abs(to.x - from.x);
	d.y = abs(to.y - from.y);
	if (d.x > d.y)
		shallow_slope(img, d, sp, color);
	else
		steep_slope(img, d, sp, color);
}
