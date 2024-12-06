#include "fdf.h"

static float to_rad(float deg)
{
	return (deg * M_PI / 180.0);
}


static t_xy_pt proj_iso_pt(t_xyz_pt *pt, int zoom)
{
	t_xy_pt proj_pt;
	float theta;

	theta = to_rad(35.26);
	proj_pt.x = zoom * (pt->x - pt->y) * cos(theta);
	proj_pt.y = zoom * ((pt->x + pt->y) * sin(theta) - pt->z);
	
	return (proj_pt);
}

static void	shift_to_center(t_xy_pt *pt)
{
	pt->x += WIDTH/2;
	pt->y += HEIGHT/2;
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
		/*ft_debug("(%d, %d) => (%d, %d)\n", from.x, from.y, to.x, to.y);*/
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
	/*ft_debug("%d %d\n", dx, dy);*/
	if (dx > dy)
		shallow_slope(img, dx, dy, from, to, color);
	else
		steep_slope(img, dx, dy, from, to, color);
}

void	draw_line_axis(t_img *img, char c, t_xyz_pt *ref, t_xyz_pt **cloud, int color, int zoom)
{
	int i;
	t_xy_pt proj_from;
	t_xy_pt proj_to;

	if (c != 'x' && c != 'y')
		return ;
	i = 0;
	while (cloud[i])
	{
		if (c = 'y' && cloud[i]->y == ref->y + 1)
		{
			proj_from = proj_iso_pt(ref, zoom);
			proj_to = proj_iso_pt(cloud[i], zoom);
			shift_to_center(&proj_from);
			shift_to_center(&proj_to);
			/*ft_debug("draw_line_axis y: %d %d\n", proj_from, proj_to);*/
			draw_line(img, proj_from, proj_to, color);
		}
		if (c = 'x' && cloud[i]->x == ref->x + 1)
		{
			proj_from = proj_iso_pt(ref, zoom);
			proj_to = proj_iso_pt(cloud[i], zoom);
			shift_to_center(&proj_from);
			shift_to_center(&proj_to);
			/*ft_debug("draw_line_axis x: %d %d | %d %d\n", proj_from, proj_to, cloud[i]->x, cloud[i]->y);*/
			draw_line(img, proj_from, proj_to, color);
		}
		i++;
	}
}

void	proj_cloud_to_img(t_xyz_pt **cloud, t_img *img, int color, int zoom)
{
	int i;
	t_xy_pt pt1;

	i = 3;
	while (cloud[i])
	{
		/*ft_debug("(%d, %d) sent to draw_line_axis\n", cloud[i]->x, cloud[i]->y );*/
		draw_line_axis(img, 'x', cloud[i], cloud, color, zoom);
		draw_line_axis(img, 'y', cloud[i], cloud, color, zoom);
		i++;
	}
}
