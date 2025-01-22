CC = cc

CFLAGS = -Wall -Wextra -Werror -g -MMD

OBJS_DIR = obj

SRCS =	src/main.c \
	src/parsing.c \
	src/vector_operation.c \
	src/vector_utils.c \
	src/matrix.c \
	src/free.c \
	src/extraction.c \
	src/utils.c \
	src/list.c \
	src/utils1.c \
	src/utils2.c \
	src/extraction2.c \
	src/my_mlx_func.c \
	src/display.c \
	src/utils3.c \
	src/intersections.c \
	src/cam_movement.c \
	src/utils4.c \
	src/canva.c \
	src/matrix_transformation.c \
	src/matrix_utils.c

DEPS = $(OBJS:.o=.d)


OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)

NAME = minirt

$(NAME): $(OBJS)
	@make bonus -C libft/
	@make -C minilibx-linux/
	$(CC) $(CFLAGS) $^ -o $@ libft/libft.a minilibx-linux/libmlx_Linux.a -lm -lXext -lX11 -lz -g
	
$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

all: $(NAME)

clean:
	@make clean -C libft/
	@make clean -C minilibx-linux/
	rm -rf $(OBJS_DIR) $(DEPS)

fclean: clean
	rm -f $(NAME)
	@make fclean -C libft/

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re