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
# define WIDTH 1920//3840
# define HEIGHT 1080//2090
# define AMP 10.0
# define KEYD 2 
# define LITLE_CROSS 17
# define NEG_COLOR 0x242424
# define O_COLOR 0x888888
# define POS_COLOR 0xffffff

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
	int			color;
}				t_xy_pt;

typedef struct s_xyz_pt
{
	float			x;
	float			y;
	float			z;
}				t_xyz_pt;

typedef struct s_map
{
	t_xyz_pt	**cld;
	t_xy_pt		size;
	float		zoom;
	t_xy_pt		offset;
	int			z_max;
	int			z_min;
}				t_map;

typedef struct s_graph
{
	void		*xsrv;
	void		*win;
	t_img		img;
	t_map		map;
}				t_graph;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}		t_rgb;

typedef struct s_rot_matrice
{
	float	aa;
	float	ab;
	float	ac;
	float	ba;
	float	bb;
	float	bc;
	float	ca;
	float	cb;
	float	cc;
}			t_rot_matrice;

// check.c
int				input_check(int ac, char **av);

//hooks.c
int				close_win(t_graph *graph);
int				close_win_and_pt_cld(t_graph *graph);
int				keyhook(int keycode, t_graph *graph);

// putmap.c
void			proj_cloud_to_img(t_map *map, t_img *img);
t_xy_pt			proj_iso_pt(t_xyz_pt *pt, t_map *map);

// get_pt_cloud.c
int				get_pt_cloud(char *file_path, t_xy_pt *i, t_map *map);
void			free_pt_cloud(t_xyz_pt **cloud);
char			**get_clean_line(int fd);

// mlx_addon.c
int				mlx_put_px(t_img *img, int x, int y, int color);

// general_utils.c
float			to_rad(float deg);

// draw_line.c
void			draw_line(t_img *img, t_xy_pt from, t_xy_pt to);

// colors.c
void			get_point_color(t_xyz_pt *pt, t_xy_pt *proj, t_map *map);

// move.c
void			front(t_map *map);
void			back(t_map *map);
void			left(t_map *map);
void			right(t_map *map);

// rotate.c
void			rotate_z(t_map *map, float amp);

// top_proj.c
void			front_proj(t_graph *graph);

#endif
