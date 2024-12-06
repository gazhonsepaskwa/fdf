#include "fdf.h"

static int	graphical_init(void **xsrv, void **win, t_img *img)
{
	*xsrv = mlx_init();
	if (*xsrv == NULL)
		return (-1);
	*win = mlx_new_window(*xsrv, WIDTH, HEIGHT, "Hello world!");
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

int	main(int ac, char **av)
{
	void		*xsrv;
	void		*win;
	t_img		img;
	t_xyz_pt	**cld;

	if (input_check(ac, av) == -1)
		return (1);
	if (graphical_init(&xsrv, &win, &img) == -1)
		return (1);
	cld = get_pt_cloud(av[1]);
	
	// test ======
	/*t_xy_pt pt1;*/
	/*t_xy_pt pt2;*/
	/*pt1.x = 5;*/
	/*pt1.y = 5;*/
	/*pt2.x = 150;*/
	/*pt2.y = 20;*/
	/**/
	/*draw_line(&img, pt1, pt2, 0x4bcec6);*/
	proj_cloud_to_img(cld, &img,  0x4bcec6 , 30);
	mlx_put_image_to_window(xsrv, win, img.self, 0, 0);
	mlx_loop(xsrv);
	mlx_destroy_display(xsrv);
	free_pt_cloud(cld);
	free(xsrv);
	return (0);
}


