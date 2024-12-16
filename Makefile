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

$(LIBFT_DIR)/$(LIBFT):
	@make -C $(LIBFT_DIR) all

init:
	@make -C $(MLX_DIR) all

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(WFLAGS) -g3 -ggdb  -c $< -o $@ # -fsanitize=address 

$(NAME): $(LIBFT_DIR)/$(LIBFT) $(OBJS)
	$(CC) $(WFLAGS) $(OBJS) $(LIBFT_DIR)/$(LIBFT) $(MLX_DIR)/$(MLX) $(BASELIB) $(XLINK) -g3 -ggdb  -o $(NAME) # -fsanitize=address

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

clean_libft:
	make -C $(LIBFT_DIR) clean

fclean_libft:
	make -C $(LIBFT_DIR) fclean

clean_all: clean clean_libft

fclean_all: fclean fclean_libft 

re: fclean all
