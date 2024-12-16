/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@sudent.s19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:19:13 by nalebrun          #+#    #+#             */
/*   Updated: 2024/12/13 15:19:58 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check.h"

static int	empty_file(int fd)
{
	char	buffer[1];
	int		tmp;

	buffer[0] = 1;
	tmp = read(fd, buffer, 1);
	if (tmp == 0 || buffer[0] == '\n')
	{
		ft_printf("%sPlease do not use an ~empty~ file\n%s", RED, RESET);
		close(fd);
		return (-1);
	}
	else
	{
		close(fd);
		return (0);
	}
}

static int	extention_check(char *file)
{
	int	len;

	len = ft_strlen(file) - 1;
	if (file[len - 2] == 'f' && file[len - 1] == 'd' && file[len] == 'f'
		&& file[len - 3] == '.')
		return (1);
	return (0);
}

static int	onlyspace(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] != 32 && str[i] != '\n')
			return (0);
	return (1);
}

static int	check_line_len(char *file_path)
{
	int		fd;
	int		len;
	char	*line;

	fd = open(file_path, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
		return (-1);
	len = getnlen(line);
	while (line != NULL)
	{
		if (len != getnlen(line) || onlyspace(line))
		{
			free(line);
			ft_printf("%sThe file is not well formated\n%s", RED, RESET);
			return (-1);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

int	input_check(int ac, char **av)
{
	int	fd;

	if (ac != 2)
		return (ft_printf("%sUsage: %s <map_file>\n%s", RED, av[0], RESET));
	fd = open(av[1], O_WRONLY);
	if (fd == -1)
		return (ft_printf("%sPlease use an existing FILE\n%s", RED, RESET));
	close(fd);
	fd = open(av[1], O_RDONLY);
	if (!extention_check(av[1]))
		return (ft_printf("%sPlease use a .fdf file\n%s", RED, RESET));
	if (empty_file(fd) == -1)
		return (-1);
	close(fd);
	if (check_line_len(av[1]) == -1)
		return (-1);
	return (0);
}
