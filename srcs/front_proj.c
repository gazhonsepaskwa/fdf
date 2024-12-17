/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   front_proj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 23:01:57 by nalebrun          #+#    #+#             */
/*   Updated: 2024/12/17 23:03:04 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	front_proj(t_graph *graph)
{
	int			i;
	int			m;
	t_xy_pt		off;
	t_xy_pt		from;
	t_xy_pt		to;

	off.y = HEIGHT / 2;
	off.x = WIDTH / 25;
	m = WIDTH / graph->map.size.x;
	i = 0;
	while (graph->map.cld[i])
	{
		if ((graph->map.cld[i + 1]) && ((i + 1) % graph->map.size.x != 0))
		{
			from.x = graph->map.cld[i]->x * m + off.x;
			from.y = graph->map.cld[i]->z * HEIGHT / 1000 + off.y;
			from.color = 0xffffff;
			to.x = graph->map.cld[i + 1]->x * m + off.x;
			to.y = graph->map.cld[i + 1]->z * HEIGHT / 1000 + off.y;
			to.color = 0xffffff;
			draw_line(&graph->img, from, to);
		}
		i++;
	}
}
