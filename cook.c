#include "fdf.h"

static int	graphical_init(void **xsrv, void **win, t_img *img)
{
	*xsrv = mlx_init();
	if (*xsrv == NULL)
		return (-1);
	*win = mlx_new_window(*xsrv, WIDTH, HEIGHT, "fdf");
	img->self = mlx_new_image(*xsrv, WIDTH, HEIGHT);
	if (*win == NULL || img->self == NULL)
		return (-1);
	img->addr = mlx_get_data_addr(img->self, &img->bpp, &img->line_len,
								&img->endian);
	if (img->addr == NULL)
		return (-1);
	return (0);
}

static int	input_check(int ac, char **av)
{
	int fd;

	if (ac != 2)
	{
		ft_printf("%sUsage : %s <map_file>\n%s", RED, av[0], RESET);
		return (-1);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		ft_printf("%sPlease use an existing file\n%s", RED, RESET);
		return (-1);
	}
	else
		close(fd);
	return (0);
}

void proj_corner(t_xyz_pt *corners[4], t_xy_pt *out[2])
{
	t_xy_pt	proj_min;
	t_xy_pt	proj_max;
	t_xy_pt	proj;
	int		i;

    proj_min.x = INT_MAX;
    proj_min.y = INT_MAX;
	proj_max.x = -INT_MAX;
	proj_max.y = -INT_MAX;
	i = -1;
    while (++i < 4)
	{
        proj = proj_iso_pt(corners[i], 1.0);
        if (proj.x < proj_min.x)
			proj_min.x = proj.x;
        if (proj.x > proj_max.x)
			proj_max.x = proj.x;
        if (proj.y < proj_min.y)
			proj_min.y = proj.y;
        if (proj.y > proj_max.y)
			proj_max.y = proj.y;
    }
	*out[0] = proj_min;
	*out[1] = proj_max; 
}

void calc_fit(t_xyz_pt **cld, t_xy_pt size, float *zoom, t_xy_pt *offset)
{
	t_xy_pt		proj[2];
	t_xyz_pt	*corners[4] = {
        &cld[0][0],
        &cld[0][size.x - 1],
        &cld[size.y - 1][0],
        &cld[size.y - 1][size.x - 1]
    };
	t_xy_pt *proj_ptr[2] = { &proj[0], &proj[1] };


	proj_corner(corners, proj_ptr);
    *zoom = fmin(
        (float)(WIDTH / (proj[1].x - proj[0].x)),
        (float)(HEIGHT / (proj[1].y - proj[0].y))
    );
    offset->x = (WIDTH / 2) - (*zoom * (proj[1].x + proj[0].x) / 2.0);
    offset->y = (HEIGHT / 2) - (*zoom * (proj[1].y + proj[0].y) / 2.0);
}

int	main(int ac, char **av)
{
	void		*xsrv;
	void		*win;
	t_img		img;
	t_xyz_pt	**cld;
	t_xy_pt		map_xy;
	float		zoom;
	t_xy_pt		offset;

	if (input_check(ac, av) == -1)
		return (1);
	if (graphical_init(&xsrv, &win, &img) == -1)
		return (1);
	/*ft_debug(" Getting point cloud...   ");*/
	cld = get_pt_cloud(av[1], &map_xy);
	/*ft_printf("[DONE]\n");*/
	/*ft_debug(" Projecting cloud...      ");*/
	calc_fit(cld, map_xy, &zoom, &offset);
	proj_cloud_to_img(cld, &img,  0x4bcec6, zoom);//zoom(cld[map_xy.x * map_xy.y - 1], HEIGHT-OFFSET)); 
	/*ft_printf("[DONE]\n");*/
	/*ft_debug(" Putting img to window... ");*/
	mlx_put_image_to_window(xsrv, win, img.self, 0, 0);
	/*ft_printf("[DONE]\n");*/
	/*ft_debug(" Render done !");*/
	mlx_loop(xsrv);
	mlx_destroy_display(xsrv);
	free_pt_cloud(cld);
	free(xsrv);
	return (0);
}


