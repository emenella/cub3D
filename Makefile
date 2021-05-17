GCC := @gcc -Wall -Werror -Wextra
LIBFT := libft.a
NAME := cub3D
SRC := ./srcs/main.c ./srcs/parser.c ./srcs/utils.c ./srcs/utils1.c ./srcs/utils2.c ./srcs/utils3.c ./srcs/utils4.c ./srcs/read_file.c ./srcs/verification_argurment.c ./srcs/mlx.c ./srcs/minimap.c ./srcs/texture.c ./srcs/sprites.c srcs/free.c srcs/save.c srcs/calculation.c srcs/color.c srcs/free1.c srcs/mlx1.c srcs/parser1.c srcs/render.c
SRCBONUS := ./srcs/main_bonus.c ./srcs/parser_bonus.c ./srcs/utils_bonus.c ./srcs/utils1_bonus.c ./srcs/utils2_bonus.c ./srcs/utils3_bonus.c ./srcs/utils4_bonus.c ./srcs/read_file_bonus.c ./srcs/verification_argurment_bonus.c ./srcs/mlx_bonus.c ./srcs/minimap_bonus.c ./srcs/texture_bonus.c ./srcs/sprites_bonus.c srcs/free_bonus.c srcs/save_bonus.c srcs/calculation_bonus.c srcs/color_bonus.c srcs/free1_bonus.c srcs/mlx1_bonus.c srcs/parser1_bonus.c srcs/render_bonus.c
HEADER := ./srcs/cub3D.h ./minilibx/mlx.h
OBJ := $(SRC:.c=.o)
OBJBONUS := $(SRCBONUS:.c=.o)
COM_STRING  = "Compiling"
COM_COLOR   = \033[0;34
NO_COLOR    = \033[m
OBJ_COLOR   = \033[0;36m


all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -C libft all
	@$(MAKE) -C minilibx all
	$(GCC) -o $(NAME) -L. -lmlx $(LIBFT) $(OBJ)
	@printf "%b" "\033[0;32m cub3D is done !$(NO_COLOR)\n"


bonus: $(OBJBONUS)
	@$(MAKE) -C libft all
	@$(MAKE) -C minilibx all
	$(GCC) -o $(NAME) -L. -lmlx $(LIBFT) $(OBJBONUS)
	@printf "%b" "\033[0;32m cub3D is done !$(NO_COLOR)\n"

%.o: %.c $(HEADER) $(SRC)
	@printf "%b" "\033c";
	@printf "%b" "$(COM_STRING) $(OBJ_COLOR)$(@)$(NO_COLOR)\n";
	$(GCC) -o $@ -c $<

clean:
	@$(MAKE) -C libft clean
	@rm -f $(OBJ) $(OBJBONUS)
	@printf "%b" "\033[0;32m clean cub3D$(NO_COLOR)\n"

fclean:
	@$(MAKE) -C libft fclean
	@$(MAKE) -C minilibx clean
	@rm -f $(NAME) $(OBJ) $(OBJBONUS)
	@printf "%b" "\033[0;32m fclean cub3D$(NO_COLOR)\n"

re: fclean all