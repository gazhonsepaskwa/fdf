#include "fdf.h"
#include <stdio.h>

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

static int zoom(t_xyz_pt *bot, int y)
{ 
	float zoom;
	float theta;

	theta = to_rad(35.26);
	zoom = (y * 2.8) / (bot->x + bot->y) * sin(theta);
	return (zoom);
}

int	main(int ac, char **av)
{
	void		*xsrv;
	void		*win;
	t_img		img;
	t_xyz_pt	**cld;
	t_xy_pt		map_xy;

	if (input_check(ac, av) == -1)
		return (1);
	if (graphical_init(&xsrv, &win, &img) == -1)
		return (1);
	ft_debug(" Getting point cloud...   ");
	cld = get_pt_cloud(av[1], &map_xy);
	ft_printf("[DONE]\n");
	ft_debug(" Projecting cloud...      ");
	proj_cloud_to_img(cld, &img,  0x4bcec6, zoom(cld[map_xy.x * map_xy.y - 1], HEIGHT-OFFSET)); 
	ft_printf("[DONE]\n");
	ft_debug(" Putting img to window... ");
	mlx_put_image_to_window(xsrv, win, img.self, 0, 0);
	ft_printf("[DONE]\n");
	ft_debug(" Render done !");
	mlx_loop(xsrv);
	mlx_destroy_display(xsrv);
	free_pt_cloud(cld);
	free(xsrv);
	return (0);
}


