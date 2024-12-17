/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 08:51:52 by nalebrun          #+#    #+#             */
/*   Updated: 2024/12/17 08:52:20 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	clean_img(t_img *img)
{
	int	i;

	i = 0;
	while (i < WIDTH * HEIGHT * 4)
	{
		img->addr[i] = 0;
		i++;
	}
}

int	keyhook(int keycode, t_graph *graph)
{
	if (keycode == XK_Escape)
		close_win_and_pt_cld(graph);
	if (keycode == XK_k)
		graph->map.zoom *= 1.2;
	if (keycode == XK_j)
		graph->map.zoom *= 0.8;
	if (keycode == XK_s)
		front(&graph->map);
	if (keycode == XK_w)
		back(&graph->map);
	if (keycode == XK_d)
		left(&graph->map);
	if (keycode == XK_a)
		right(&graph->map);
	if (keycode == XK_u)
		rotate_z(&graph->map, M_PI / 16);
	if (keycode == XK_i)
		rotate_z(&graph->map, -M_PI / 16);
	clean_img(&graph->img);
	proj_cloud_to_img(&graph->map, &graph->img);
	mlx_put_image_to_window(graph->xsrv, graph->win, graph->img.self, 0, 0);
	return (0);
}
