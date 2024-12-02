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
	if (ac != 2)
	{
		ft_printf("%sUsage : %s <map_file>\n%s", RED, av[0], RESET);
		return (-1);
	}
}

int	main(int ac, char **av)
{
	void	*xsrv;
	void	*win;
	t_img	img;
	int		**normap;

	if (input_check(ac, av) == -1)
		return (1);
	//normap = getfile(av[1]);	
	//if (graphical_init(&xsrv, &win, &img) == -1)
		//return (1);
	
	ft_printf("pts in cloud : %d", count_pts(av[1]));
	//mlx_put_image_to_window(xsrv, win, img.self, 0, 0);
	//mlx_loop(xsrv);
	//mlx_destroy_display(mlx);
	//free(mlx);
	return (0);
}
