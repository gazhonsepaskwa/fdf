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

#include "fdf.h"
#include "get_pt_cloud.h"

static void	ft_free_s_tab(char **tab)
{
	int	i;

	if (tab == NULL)
		return ;
	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

static int	build_cloud(t_xy_pt *i, char **tab, t_xyz_pt **cloud, int fd)
{
	int	lst_pt;

	i->y = 0;
	lst_pt = 0;
	tab = get_clean_line(fd);
	if (tab == NULL)
		return (-1);
	while (tab && tab[0] != NULL)
	{
		i->x = 0;
		while (tab[i->x] != 0)
		{
			cloud[lst_pt] = ft_calloc(1, sizeof(t_xyz_pt));
			set_xyz_pt(cloud[lst_pt++], i->x, i->y, ft_atoi(tab[i->x]));
			i->x++;
		}
		ft_free_s_tab(tab);
		tab = get_clean_line(fd);
		i->y++;
	}
	return (lst_pt);
}

t_xyz_pt	**get_pt_cloud(char *file_path, t_xy_pt *i)
{
	t_xyz_pt	**cloud;
	int			fd;
	char		**tab;
	int			lst_pt;

	tab = NULL;
	cloud = malloc((count_pts(file_path) + 1) * sizeof(t_xyz_pt *));
	fd = open(file_path, O_RDONLY);
	lst_pt = build_cloud(i, tab, cloud, fd);
	cloud[lst_pt] = NULL;
	ft_free_s_tab(tab);
	return (cloud);
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
