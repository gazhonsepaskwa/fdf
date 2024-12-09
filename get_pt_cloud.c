#include "fdf.h"

void	nl_to_sp(unsigned int unused, char *c)
{
	(void)unused;
	if (*c == '\n')
		*c = ' ';
}

int count_pts_inln(char *ln)
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

int count_pts(char *file_path)
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

char **get_clean_line(int fd)
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

void set_xyz_pt(t_xyz_pt *pt, int x, int y, int z)
{
	pt->x = x;
	pt->y = y;
	pt->z = z;
}

void	ft_free_s_tab(char **tab)
{
	int i;
	
	if (tab == NULL)
		return ;
	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

t_xyz_pt	**get_pt_cloud(char *file_path, t_xy_pt *i)
{
	t_xyz_pt	**cloud;
	int			fd;
	char		**tab;
	int			lst_pt;

	cloud = malloc((count_pts(file_path) + 1) * sizeof(t_xyz_pt *));
	fd = open(file_path, O_RDONLY);
	tab = get_clean_line(fd);
	if (tab == NULL)
		return(NULL);
	lst_pt = 0;
	i->y = 0;
	while(tab && tab[0] != NULL)
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
	cloud[lst_pt] = NULL;
	ft_free_s_tab(tab);
	return (cloud);
}

void free_pt_cloud(t_xyz_pt **cloud)
{
	int i;

	i = -1;
	while(cloud[++i])
		free(cloud[i]);
	free(cloud);
	cloud = NULL;
}
