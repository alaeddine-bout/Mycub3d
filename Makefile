NAME = cub3d

BONUS_NAME = cub3d_bonus

CFLAGS = -Wall -Wextra -Werror -O3 -Ofast -fsanitize=address -g3

SRCS = 	./src/cub3d.c\
		./src/readfile.c\
		./src/utils.c\
		./src/maparse.c\
		./src/parse_colors.c\
		./src/parse_textures.c\
		./get_next_line/get_next_line.c\
		./get_next_line/get_next_line_utils.c\
		./src/initgame.c\
		./src/player_movements.c\
		./src/raycasting.c\
		./src/render.c\
		./src/utils2.c\

BONUS = ./src_bonus/cub3d_bonus.c\
		./src_bonus/readfile_bonus.c\
		./src_bonus/utils_bonus.c\
		./src_bonus/maparse_bonus.c\
		./src_bonus/parse_colors_bonus.c\
		./src_bonus/parse_textures_bonus.c\
		./get_next_line/get_next_line.c\
		./get_next_line/get_next_line_utils.c\
		./src_bonus/initgame_bonus.c\
		./src_bonus/bonus_part.c\
		./src_bonus/player_movements_bonus.c\
		./src_bonus/raycasting_bonus.c\
		./src_bonus/render_bonus.c\
		./src_bonus/utils2_bonus.c\

CC = cc

all: $(NAME)


$(NAME):$(SRCS)
	@make -C libft -s 
	@$(CC) $(CFLAGS) $(SRCS) ./libft/libft.a -lmlx -lXext -lX11 -lm -lmcheck -o $(NAME)
	@echo "\033[1;32mCub3d is ready to execute ✅\033[0m"

bonus : $(BONUS_NAME)

$(BONUS_NAME) : $(BONUS)
	@make -C libft -s 
	@$(CC) $(CFLAGS) $(BONUS) ./libft/libft.a -lmlx -lXext -lX11 -lm -lmcheck -o $(BONUS_NAME)
	@echo "\033[1;32mCub3d_bonus is ready to execute ✅\033[0m"

clean:
	@make  -C libft -s  clean
	@echo "\033[1;31mObject files deleted successfully 🗑\033[0m"

fclean: clean
	@rm -f $(BONUS_NAME)
	@rm -f $(NAME)
	@make -C libft -s  fclean
	@echo "\033[1;31mExecution file deleted successfully 🗑\033[0m"

re:	fclean all

.PHONY:	all bonus clean fclean re