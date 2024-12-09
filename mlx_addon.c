#include "fdf.h"

int mlx_put_px(t_img *img, int x, int y, int color)
{
    char    *pixel;
	if (x > WIDTH || y > HEIGHT || x < 0 || y < 0)
	{
		/*ft_printf("%s\n[NOT RENDERED] (%d, %d)%s\n", RED, x, y, RESET);*/
		return (-1);
	}
    pixel = img->addr + ((y * img->line_len) + (x * (img->bpp/ 8)));
    *(unsigned int*)pixel = color;
	return (0);
}
