#include "fdf.h"

float to_rad(float deg)
{
	return (deg * M_PI / 180.0);
}

static t_xy_pt iso_proj(t_xyz_pt *pt, int zoom)
{
	t_xy_pt proj_pt;
	float theta;

	theta = to_rad(35.26);
	proj_pt.x = zoom * (pt->x - pt->y) * cos(theta);
	proj_pt.y = zoom * ((pt->x + pt->y) * sin(theta) - pt->z);
	
	return (proj_pt);
}
