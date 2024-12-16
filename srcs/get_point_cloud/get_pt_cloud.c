/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pt_cloud.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:34:17 by nalebrun          #+#    #+#             */
/*   Updated: 2024/12/10 17:34:28 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"
#include "get_pt_cloud.h"

static void	update_min_max(int z, t_map *map)
{
	if (z > map->z_max)
		map->z_max = z;
	if (z < map->z_min)
		map->z_min = z;
}

static int	build_cloud(t_xy_pt *i, char **tab, t_map *map, int fd)
{
	int	lst_pt;
	int	tmp_z;

	i->y = 0;
	lst_pt = 0;
	tmp_z = 0;
	tab = get_clean_line(fd);
	if (tab == NULL)
		return (-1);
	while (tab && tab[0] != NULL)
	{
		i->x = 0;
		while (tab[i->x] != 0)
		{
			map->cld[lst_pt] = ft_calloc(1, sizeof(t_xyz_pt));
			tmp_z = ft_atoi(tab[i->x]);
			update_min_max(tmp_z, map);
			set_xyz_pt(map->cld[lst_pt++], i->x, i->y, tmp_z);
			i->x++;
		}
		ft_free_c_tab(tab);
		tab = get_clean_line(fd);
		i->y++;
	}
	close(fd);
	return (lst_pt);
}

int	get_pt_cloud(char *file_path, t_xy_pt *i, t_map *map)
{
	int			fd;
	char		**tab;
	int			lst_pt;
	int			pts_count;

	tab = NULL;
	pts_count = count_pts(file_path);
	if (pts_count == -1)
		return (-1);
	map->cld = malloc((pts_count + 1) * sizeof(t_xyz_pt *));
	if (!map->cld)
		return (-1);
	fd = open(file_path, O_RDONLY);
	map->z_max = 0;
	map->z_min = 0;
	lst_pt = build_cloud(i, tab, map, fd);
	map->cld[lst_pt] = NULL;
	ft_free_c_tab(tab);
	return (0);
}

void	free_pt_cloud(t_xyz_pt **cloud)
{
	int	i;

	i = -1;
	while (cloud[++i])
		free(cloud[i]);
	free(cloud);
	cloud = NULL;
}
