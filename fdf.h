#include "mlx_linux/mlx.h"
#include <math.h>
#include "libft/libft.h"
#include <fcntl.h>

//struct
typedef struct s_img {
	void	*self;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_xy_pt {
	int x;
	int y;
}	t_xy_pt;

typedef struct s_xyz_pt {
	int x;
	int y;
	int z;
}	t_xyz_pt;

// define
#define WIDTH 1080
#define HEIGHT 720
#define X_OFFSET 10
#define Y_OFFSET 10
#define TETA 30

// putmap
void	proj_cloud_to_img(t_xyz_pt **cloud, t_img *img, int color, int zoom);

// get_pt_cloud.c
t_xyz_pt	**get_pt_cloud(char *file_path);
void free_pt_cloud(t_xyz_pt **cloud);

// mlx_addon.c
void mlx_put_px(t_img *img, int x, int y, int color);

// test_fcts.c
void test_cloud(char *file_path);



// tempo 

void	draw_line(t_img *img, t_xy_pt from, t_xy_pt to, int color);
