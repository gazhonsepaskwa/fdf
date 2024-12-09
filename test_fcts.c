#include "fdf.h"

void test_cloud(char *file_path)
{
	int i = 0;
	t_xyz_pt	**cld;
	t_xy_pt		unused;

	ft_debug(" ===\n");
	cld = get_pt_cloud(file_path, &unused);
	while (cld[i] != NULL)
	{ft_debug(" %d (%d, %d, %d)\n", i+1, cld[i]->x, cld[i]->y, cld[i]->z); i++;}
	ft_debug(" ===\n");
	free_pt_cloud(cld);
}
