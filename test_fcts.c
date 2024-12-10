/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_fcts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:35:12 by nalebrun          #+#    #+#             */
/*   Updated: 2024/12/10 17:35:14 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	test_cloud(char *file_path)
{
	int			i;
	t_xyz_pt	**cld;
	t_xy_pt		unused;

	i = 0;
	ft_debug(" ===\n");
	cld = get_pt_cloud(file_path, &unused);
	while (cld[i] != NULL)
	{
		ft_debug(" %d (%d, %d, %d)\n", i + 1, cld[i]->x, cld[i]->y, cld[i]->z);
		i++;
	}
	ft_debug(" ===\n");
	free_pt_cloud(cld);
}
