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
		/*ft_debug("%d", count);*/
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

t_xyz_pt	*get_pt_cloud(char *file_path)
{
	t_xyz_pt	*cloud;

	cloud = ft_calloc(count_pts(file_path), sizeof(t_xyz_pt));
}
