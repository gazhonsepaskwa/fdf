/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_point_cloud_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:46:06 by nalebrun          #+#    #+#             */
/*   Updated: 2024/12/11 11:46:38 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	nl_to_sp(unsigned int unused, char *c)
{
	(void)unused;
	if (*c == '\n')
		*c = ' ';
}

int	count_pts_inln(char *ln)
{
	int	i;
	int	count;

	i = 0;
	while (ln[i + 1])
	{
		if (!ft_isdigit(ln[i]) && ft_isdigit(ln[i + 1]))
			count++;
		i++;
	}
	count++;
	return (count);
}

int	count_pts(char *file_path)
{
	char	*line;
	int		count;
	int		fd;

	fd = open(file_path, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
		return (-1);
	count = 0;
	while (line != NULL)
	{
		ft_striteri(line, nl_to_sp);
		count += count_pts_inln(line);
		ft_free(&line);
		line = get_next_line(fd);
	}
	close(fd);
	ft_free(&line);
	return (count);
}

char	**get_clean_line(int fd)
{
	char	**tab;
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (NULL);
	ft_striteri(line, nl_to_sp);
	tab = ft_split(line, ' ');
	ft_free(&line);
	return (tab);
}

void	set_xyz_pt(t_xyz_pt *pt, int x, int y, int z)
{
	pt->x = x;
	pt->y = y;
	pt->z = z;
}
