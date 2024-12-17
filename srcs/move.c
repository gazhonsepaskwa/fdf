/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:39:22 by nalebrun          #+#    #+#             */
/*   Updated: 2024/12/17 15:39:50 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	front(t_map *map)
{
	int	i;

	i = 0;
	while (map->cld[i])
	{
		map->cld[i]->x -= 100 / map->zoom;
		map->cld[i]->y -= 100 / map->zoom;
		i++;
	}
}

void	back(t_map *map)
{
	int	i;

	i = 0;
	while (map->cld[i])
	{
		map->cld[i]->x += 100 / map->zoom;
		map->cld[i]->y += 100 / map->zoom;
		i++;
	}
}

void	left(t_map *map)
{
	int	i;

	i = 0;
	while (map->cld[i])
	{
		map->cld[i]->x -= 100 / map->zoom;
		map->cld[i]->y += 100 / map->zoom;
		i++;
	}
}

void	right(t_map *map)
{
	int	i;

	i = 0;
	while (map->cld[i])
	{
		map->cld[i]->x += 100 / map->zoom;
		map->cld[i]->y -= 100 / map->zoom;
		i++;
	}
}
