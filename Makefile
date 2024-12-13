CC = gcc
WFLAGS = -Wall -Werror -Wextra
BASE_LIB = -L/usr/lib 
XLINK = -lXext -lX11 -lm -lz 

SRCDIR = srcs
OBJDIR = objs
INCDIR = .
LIBFT_DIR = lib/libft
MLX_DIR = lib/mlx_linux

NAME = fdf
LIBFT = libft.a -Ilibft
MLX = libmlx.a -Imlx_linux

SRCS = $(shell find $(SRCDIR) -name "*.c")
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

.PHONY: all clean fclean re

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR) all
	@echo "libft made"

init:
	@make -C $(MLX_DIR) all

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(WFLAGS) -g3 -ggdb -c $< -o $@

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(WFLAGS) $(OBJS) $(LIBFT_DIR)/$(LIBFT) $(MLX_DIR)/$(MLX) $(BASELIB) $(XLINK) -g3 -ggdb -o $(NAME)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

clean_libft:
	make -C $(LIBFT_DIR) clean

fclean_libft:
	make -C $(LIBFT_DIR) fclean

re: fclean all
