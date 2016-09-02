NAME =					ft_otool
CC =					clang
INCLUDES_DIR =			./includes/
SRCS_DIR =				./srcs/
OBJ_DIR =				./obj/
LIBFT_DIR =				../libft
LIBFT_INCLUDES =		$(LIBFT_DIR)/includes/
LIBFT =					$(LIBFT_DIR)/libft.a
CFLAGS =				-Wall -Wextra -Werror -I$(INCLUDES_DIR) -I$(LIBFT_INCLUDES) -c -g -o
LDFLAGS =				-L$(LIBFT_DIR) -lft -o
SRCS =					get_handler.c\
						get_text_section.c\
						handle_64.c\
						handle_32.c\
						load_file.c\
						main.c\
						print_text.c
OBJ =					$(SRCS:.c=.o)

all: $(LIBFT) $(OBJ_DIR) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(OBJ_DIR):
	mkdir -p $@

$(NAME): $(addprefix $(OBJ_DIR), $(OBJ))
	$(CC) $(LDFLAGS) $@ $^

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c
	$(CC) $(CFLAGS) $@ $<

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: clean fclean
	make -C $(LIBFT_DIR) fclean
	make all

.PHONY: all clean fclean re
