/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:43:57 by nalebrun          #+#    #+#             */
/*   Updated: 2024/12/17 16:44:36 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	pt_time_rot_mat(t_xyz_pt *ma, t_rot_matrice *mb)
{
	t_xyz_pt	tmp;

	tmp.x = (ma->x * mb->aa) + (ma->y * mb->ab) + (ma->z * mb->ac);
	tmp.y = (ma->x * mb->ba) + (ma->y * mb->bb) + (ma->z * mb->bc);
	tmp.z = (ma->x * mb->ca) + (ma->y * mb->cb) + (ma->z * mb->cc);
	ma->x = tmp.x;
	ma->y = tmp.y;
	ma->z = tmp.z;
}

void	rotate_z(t_map *map, float amp)
{
	int				i;
	t_rot_matrice	z_rotation;

	z_rotation.aa = cos(amp);
	z_rotation.ab = -sin(amp);
	z_rotation.ac = 0;
	z_rotation.ba = sin(amp);
	z_rotation.bb = cos(amp);
	z_rotation.bc = 0;
	z_rotation.ca = 0;
	z_rotation.cb = 0;
	z_rotation.cc = 1;
	i = 0;
	while (map->cld[i])
	{
		pt_time_rot_mat(map->cld[i], &z_rotation);
		i++;
	}
}
