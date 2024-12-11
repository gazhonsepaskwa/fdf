cc -Wall -Werror -Wextra *.c mlx_linux/libmlx.a libft/libft.a -Lmlx_linux -Llibft -L/usr/lib -Imlx_linux -Ilibft -lXext -lX11 -lm -lz -g3 -ggdb -fsanitize=address
