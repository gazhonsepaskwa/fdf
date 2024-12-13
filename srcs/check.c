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

#include "../fdf.h"

static int empty_file(int fd)
{
	char buffer[1];
	buffer[1]= 1;
	if (read(fd, buffer, 1) == 0)
	{
		ft_printf("%sPlease do not use an empty file\n%s", RED, RESET);
		close(fd);
		return (-1);
	}
	else 
	{
		close(fd);
		ft_printf("%s{???}|%s|\n%s", RED,buffer, RESET);
		return (0);
	}

}

int	input_check(int ac, char **av)
{
	int	fd;

	if (ac != 2)
	{
		ft_printf("%sUsage : %s <map_file>\n%s", RED, av[0], RESET);
		return (-1);
	}
	fd = open(av[1], O_WRONLY);
	if (fd == -1)
	{
		ft_printf("%sPlease use an existing file\n%s", RED, RESET);
		return (-1);
	}
	else
	{
		close(fd);
		fd = open(av[1], O_RDONLY);
		return(empty_file(fd));
	}
	return (0);
}
