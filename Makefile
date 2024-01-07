NAME = minishell

ifeq ($(shell uname -p), i386)
    LIB_FLAGS   =   -L./lib/libft -lft -L/usr/local/Cellar/readline/8.1/lib -lreadline
    INCLUDES    =   -I./include -I./lib/libft -I/usr/local/Cellar/readline/8.1/include
else
    LIB_FLAGS   =   -L./lib/libft -lft -lreadline
    INCLUDES    =   -I./include -I./lib/libft
endif

SRC = main.c Parsing/tokeniser.c Parsing/ft_splitter.c Parsing/syntax_analyzer.c Parsing/utils.c Execution/Builtins/builtins.c

OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -g3 -Wall -Werror -Wextra

LIB = Libft/libft.a
GNL = Libft/get_next_line/get_next_line.a

GREEN = \033[0;32m
NC = \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@make -sC ./Libft
	@$(CC) $(CFLAGS) $(OBJ) $(LIB) -lreadline -o $(NAME)
	@echo -e "$(GREEN)   ___                       ___                       ___           ___           ___           ___       ___ \n     /\__\          ___        /\__\          ___        /\  \         /\__\         /\  \         /\__\     /\__\n    /::|  |        /\  \      /::|  |        /\  \      /::\  \       /:/  /        /::\  \       /:/  /    /:/  /\n   /:|:|  |        \:\  \    /:|:|  |        \:\  \    /:/\ \  \     /:/__/        /:/\:\  \     /:/  /    /:/  / \n  /:/|:|__|__      /::\__\  /:/|:|  |__      /::\__\  _\:\~\ \  \   /::\  \ ___   /::\~\:\  \   /:/  /    /:/  /  \n /:/ |::::\__\  __/:/\/__/ /:/ |:| /\__\  __/:/\/__/ /\ \:\ \ \__\ /:/\:\  /\__\ /:/\:\ \:\__\ /:/__/    /:/__/   \n \/__/~~/:/  / /\/:/  /    \/__|:|/:/  / /\/:/  /    \:\ \:\ \/__/ \/__\:\/:/  / \:\~\:\ \/__/ \:\  \    \:\  \   \n       /:/  /  \::/__/         |:/:/  /  \::/__/      \:\ \:\__\        \::/  /   \:\ \:\__\    \:\  \    \:\  \  \n      /:/  /    \:\__\         |::/  /    \:\__\       \:\/:/  /        /:/  /     \:\ \/__/     \:\  \    \:\  \ \n     /:/  /      \/__/         /:/  /      \/__/        \::/  /        /:/  /       \:\__\        \:\__\    \:\__\ \n     \/__/                     \/__/                     \/__/         \/__/         \/__/         \/__/     \/__/ \nminishell is ready!$(NC)"

clean:
	@rm -f $(OBJ)
	@make clean -sC ./Libft

fclean: clean
	@rm -f $(NAME)
	@make fclean -sC ./Libft

re: fclean all

.PHONY: all clean fclean re
