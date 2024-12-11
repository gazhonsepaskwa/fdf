/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:32:57 by nalebrun          #+#    #+#             */
/*   Updated: 2024/12/11 09:26:04 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	graph_init(t_graph *g)
{
	g->xsrv = mlx_init();
	if (g->xsrv == NULL)
		return (-1);
	g->win = mlx_new_window(g->xsrv, WIDTH, HEIGHT, "fdf");
	g->img.self = mlx_new_image(g->xsrv, WIDTH, HEIGHT);
	if (g->win == NULL || g->img.self == NULL)
		return (-1);
	g->img.addr = mlx_get_data_addr(g->img.self, &g->img.bpp,
			&g->img.line_len, &g->img.endian);
	if (g->img.addr == NULL)
		return (-1);
	return (0);
}

static int	input_check(int ac, char **av)
{
	int	fd;

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

void	proj_corner(t_xyz_pt *corners[4], t_xy_pt *out[2])
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

void	calc_fit(t_map *map)
{
	t_xy_pt		proj[2];
	t_xy_pt		*proj_ptr[2];
	t_xyz_pt	*corners[4];

	proj_ptr[0] = &proj[0];
	proj_ptr[1] = &proj[1];
	corners[0] = map->cld[0];
	corners[1] = map->cld[map->size.x - 1];
	corners[2] = map->cld[((map->size.y - 1) * (map->size.x))];
	corners[3] = map->cld[(map->size.y) * (map->size.x) - 1];
	proj_corner(corners, proj_ptr);
	map->zoom = 0.6 * fmin((float)(WIDTH / (proj[1].x - proj[0].x)),
			(float)(HEIGHT / (proj[1].y - proj[0].y)));
	map->offset.x = (WIDTH / 2) - (map->zoom * (proj[1].x + proj[0].x) / 2.0);
	map->offset.y = (HEIGHT / 2) - (map->zoom * (proj[1].y + proj[0].y) / 2.0);
}

int	main(int ac, char **av)
{
	t_graph	graph;
	t_map	map;

	if (input_check(ac, av) == -1)
		return (1);
	if (graph_init(&graph) == -1)
		return (1);
	ft_printf("%s[info]%s Getting point cloud...   ", BOLD_CYAN, RESET);
	map.cld = get_pt_cloud(av[1], &map.size);
	ft_printf("[DONE]\n");
	calc_fit(&map);
	ft_printf("%s[info]%s Projecting cloud...      ", BOLD_CYAN, RESET);
	proj_cloud_to_img(&map, &graph.img, 0x4bcec6);
	ft_printf("[DONE]\n");
	ft_printf("%s[info]%s Putting img to window... ", BOLD_CYAN, RESET);
	mlx_put_image_to_window(graph.xsrv, graph.win, graph.img.self, 0, 0);
	ft_printf("[DONE]\n");
	ft_printf("%s[info]%s Render done !", BOLD_CYAN, RESET);
	mlx_loop(graph.xsrv);
	mlx_destroy_display(graph.xsrv);
	free_pt_cloud(map.cld);
	free(graph.xsrv);
	return (0);
}
