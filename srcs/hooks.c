#include "../fdf.h"

int	close_win_and_pt_cld(t_graph *graph)
{
	mlx_destroy_image(graph->xsrv, graph->img.self);
	mlx_destroy_window(graph->xsrv, graph->win);
	mlx_destroy_display(graph->xsrv);
	free(graph->xsrv);
	free_pt_cloud(graph->map.cld);
	exit(EXIT_SUCCESS);
}

int	close_win(t_graph *graph)
{
	mlx_destroy_image(graph->xsrv, graph->img.self);
	mlx_destroy_window(graph->xsrv, graph->win);
	mlx_destroy_display(graph->xsrv);
	free(graph->xsrv);
	exit(EXIT_SUCCESS);
}

int	keyhook(int keycode, t_graph *graph)
{
	(void)graph;
	if (keycode == XK_Escape)
		close_win_and_pt_cld(graph);
	return (0);
}
