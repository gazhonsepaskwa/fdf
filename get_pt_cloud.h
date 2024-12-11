/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pt_cloud.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <mnalebrun@student.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:50:54 by nalebrun          #+#    #+#             */
/*   Updated: 2024/12/11 11:51:35 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_PT_CLOUD_H
# define GET_PT_CLOUD_H 

void	nl_to_sp(unsigned int unused, char *c);
int		count_pts_inln(char *ln);
int		count_pts(char *file_path);
char	**get_clean_line(int fd);
void	set_xyz_pt(t_xyz_pt *pt, int x, int y, int z);

#endif
