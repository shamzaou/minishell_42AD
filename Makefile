
SRC =	\

OBJ = $(SRC:.c=.o)

CC = gcc -g3 
# -fsanitize=address

OBJ = $(SRC:.c=.o)

NAME = minishell

LIB = Libft/libft.a

GNL = Libft/get_next_line/get_next_line.a

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	@make -sC ./Libft
	@$(CC) $(CFLAGS) $(OBJ) $(LIB) $(PRINTF) -o $(NAME)

clean:
	@rm -f $(OBJ)
	@make clean -sC ./Libft

fclean: clean
	@rm -f $(NAME)
	@make fclean -sC ./Libft

re: fclean all

.PHONY: all clean fclean re