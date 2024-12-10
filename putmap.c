#include "fdf.h"

t_xy_pt proj_iso_pt(t_xyz_pt *pt, float zoom)
{
	t_xy_pt proj_pt;
	float theta;
	float z;

	theta = to_rad(35.61);
	proj_pt.x = zoom * (pt->x - pt->y) * cos(theta);
	if (AMP != 0)
		z = pt->z*(AMP+10)/100;
	else
		z = pt->z*(AMP)/100;
	proj_pt.y = zoom * ((pt->x + pt->y) * sin(theta) - z);
	
	return (proj_pt);
}

static void	shift_to_center(t_xy_pt *pt)
{
	pt->x += WIDTH/2;
	pt->y += OFFSET;
}

int	get_direction(int pt, int pt_)
{
	if (pt < pt_)
		return (1);
	else
		return (-1);
}

// em = error margin
void	shallow_slope(t_img *img, int dx, int dy, t_xy_pt from, t_xy_pt to, int color)
{
	int	sx;
	int	sy;
	int em;

	sx = get_direction(from.x, to.x);
	sy = get_direction(from.y, to.y);
	em = (int)(dx / 2);
	while (from.x != to.x)
	{
		mlx_put_px(img, from.x, from.y, color);
		from.x += sx;
		em -= dy;
		if (em < 0)
		{
			from.y += sy;
			em += dx;
		}
	}
}

void	steep_slope(t_img *img, int dx, int dy, t_xy_pt from, t_xy_pt to, int color)
{
	int	sx;
	int	sy;
	int em;

	sx = get_direction(from.x, to.x);
	sy = get_direction(from.y, to.y);
	em = (int)(dy / 2);
	while (from.y != to.y)
	{
		mlx_put_px(img, from.x, from.y, color);
		from.y += sy;
		em -= dx;
		if (em < 0)
		{
			from.x += sx;
			em += dy;
		}
	}
}
void	draw_line(t_img *img, t_xy_pt from, t_xy_pt to, int color)
{
	int dx;
	int dy;

	dx = abs(to.x - from.x);
	dy = abs(to.y - from.y);
	if (dx > dy)
		shallow_slope(img, dx, dy, from, to, color);
	else
		steep_slope(img, dx, dy, from, to, color);
}

void	draw_line_axis(t_img *img, t_xyz_pt *ref, t_xyz_pt **cloud, int color, float zoom)
{
	int i;
	t_xy_pt proj_from;
	t_xy_pt proj_to;

	i = 0;
	while (cloud[i])
	{
		if (cloud[i]->y == ref->y + 1 && ref->x == cloud[i]->x)
		{
			proj_from = proj_iso_pt(ref, zoom);
			proj_to = proj_iso_pt(cloud[i], zoom);
			shift_to_center(&proj_from);
			shift_to_center(&proj_to);
			draw_line(img, proj_from, proj_to, color);
		}
		if (cloud[i]->x == ref->x + 1 && ref->y == cloud[i]->y)
		{
			proj_from = proj_iso_pt(ref, zoom);
			proj_to = proj_iso_pt(cloud[i], zoom);
			shift_to_center(&proj_from);
			shift_to_center(&proj_to);
			draw_line(img, proj_from, proj_to, color);
		}
		i++;
	}
}

void	proj_cloud_to_img(t_xyz_pt **cloud, t_img *img, int color, float zoom)
{
	int i;

	i = 0;
	while (cloud[i])
	{
		draw_line_axis(img, cloud[i], cloud, color, zoom);
		i++;
	}
}
