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
#ifndef NULL
# define NULL (void *)0
#endif
#define WIDTH 500
#define HEIGHT 500
#define X_OFFSET 10
#define Y_OFFSET 10
#define TETA 30

// get_file.c
int	**getfile(char *file_path);

// mlx_addon.c
void mlx_put_px(t_img *img, int x, int y, int color);




// tmp for test

int count_pts(char *file_path);
