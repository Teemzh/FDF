NAME = FDF
NAME = $(OBJ_MAIN) $(OBJ_FDF) $(OBJ_FDF_UTILS) $(OBJ_FDF_UTILS2) $(OBJ_FDF_UTILS3) $(OBJ_FDF_UTILS4) $(OBJ_FDF_UTILS5) $(OBJ_FDF_UTILS6) $(OBJ_FDF_UTILS7)
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
OBJ_MAIN = main.o
OBJ_FDF = fdf.o
OBJ_FDF_UTILS = fdf_utils.o
OBJ_FDF_UTILS2 = fdf_utils2.o
OBJ_FDF_UTILS3 = fdf_utils3.o
OBJ_FDF_UTILS4 = fdf_utils4.o
OBJ_FDF_UTILS5 = fdf_utils5.o
OBJ_FDF_UTILS6 = fdf_utils6.o
OBJ_FDF_UTILS7 = fdf_utils7.o

MINILIBX_PATH = minilibx_macos
MINILIBX_LIB = $(MINILIBX_PATH)/libmlx.a
MINILIBX_INC = -I$(MINILIBX_PATH)

fdf_utils:
	$(CC) $(CFLAGS) -c fdf_utils.c -o fdf_utils.o

fdf_utils2:
	$(CC) $(CFLAGS) -c fdf_utils2.c -o fdf_utils2.o

fdf_utils3:
	$(CC) $(CFLAGS) -c fdf_utils3.c -o fdf_utils3.o

fdf_utils4:
	$(CC) $(CFLAGS) -c fdf_utils4.c -o fdf_utils4.o

main.o: main.c fdf.h
	$(CC) $(CFLAGS) $(MINILIBX_INC) -c main.c -o main.o

fdf.o: fdf.c fdf.h
	$(CC) $(CFLAGS) $(MINILIBX_INC) -c fdf.c -o fdf.o

all: ft_printf gnl $(MINILIBX_LIB) $(NAME)
	$(CC) $(CFLAGS) -o fdf $(NAME)  -Lft_printf -lftprintf -Lgnl -lgnl -L$(MINILIBX_PATH) -lmlx -framework OpenGL -framework AppKit

$(MINILIBX_LIB):
	$(MAKE) -C $(MINILIBX_PATH)

ft_printf:
	$(MAKE) -C ft_printf

gnl:
	$(MAKE) -C gnl

clean:
	$(MAKE) -C ft_printf clean
	$(MAKE) -C gnl clean
	rm -f $(NAME)

fclean: clean
	$(MAKE) -C ft_printf fclean
	$(MAKE) -C gnl fclean
	rm -f fdf

re: fclean all

.PHONY: all clean fclean re ft_printf gnl
