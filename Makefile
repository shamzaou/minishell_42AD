NAME = minishell

SRC =  main.c Parsing/tokeniser.c Parsing/ft_splitter.c Parsing/syntax_analyzer.c Parsing/utils.c Execution/Builtins/builtins.c

OBJ = $(SRC:.c=.o)

CC = cc -g3 
# -fsanitize=address

OBJ = $(SRC:.c=.o)

LIB = Libft/libft.a

GNL = Libft/get_next_line/get_next_line.a

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	@make -sC ./Libft
	@$(CC) $(CFLAGS) $(OBJ) $(LIB) $(PRINTF) -lreadline -o $(NAME)

clean:
	@rm -f $(OBJ)
	@make clean -sC ./Libft

fclean: clean
	@rm -f $(NAME)
	@make fclean -sC ./Libft

re: fclean all

.PHONY: all clean fclean re