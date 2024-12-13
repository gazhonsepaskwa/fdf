/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:33:51 by nalebrun          #+#    #+#             */
/*   Updated: 2024/12/11 09:37:24 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "lib/libft/libft.h"
# include "lib/mlx_linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <X11/keysym.h>

// define
# define WIDTH 3840
# define HEIGHT 2090
# define AMP 10
# define M_KEYD 1L<<0
# define KEYD 2 
# define LITLE_CROSS 17

// structs
typedef struct s_img
{
	void		*self;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}				t_img;

typedef struct s_xy_pt
{
	int			x;
	int			y;
}				t_xy_pt;

typedef struct s_xyz_pt
{
	int			x;
	int			y;
	int			z;
}				t_xyz_pt;

typedef struct s_map
{
	t_xyz_pt	**cld;
	t_xy_pt		size;
	float		zoom;
	t_xy_pt		offset;
}				t_map;

typedef struct s_graph
{
	void		*xsrv;
	void		*win;
	t_img		img;
	t_map		map;
}				t_graph;

// check.c
int	input_check(int ac, char **av);

// putmap.c
void			proj_cloud_to_img(t_map *map, t_img *img, int color);
t_xy_pt			proj_iso_pt(t_xyz_pt *pt, float zoom);

// get_pt_cloud.c
t_xyz_pt		**get_pt_cloud(char *file_path, t_xy_pt *i);
void			free_pt_cloud(t_xyz_pt **cloud);
char			**get_clean_line(int fd);

// mlx_addon.c
int				mlx_put_px(t_img *img, int x, int y, int color);

// test_fcts.c
void			test_cloud(char *file_path);

// general_utils.c
float			to_rad(float deg);

// draw_line.c
void			draw_line(t_img *img, t_xy_pt from, t_xy_pt to, int color);

#endif
