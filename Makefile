NAME = minishell

CC = cc

CFLAGS = -g3 -Wall -Werror -Wextra

ifeq ($(shell uname -m), i386)
    LIB_FLAGS   =   -L./lib/libft -lft -L/lib -lreadline
    INCLUDES    =   -I./include -I./lib/libft -I/include
else
    LIB_FLAGS   =   -L./lib/libft -lft -lreadline
    INCLUDES    =   -I./include -I./lib/libft
endif

SRC =	./main.c \
		./Env/env.c \
		./Env/env_utils.c \
		./Execution/exec_redir.c \
		./Execution/exec.c \
		./Execution/toolbox0.c \
		./Execution/exec_cmd.c \
		./Execution/queue.c \
		./Execution/queue1.c \
		./Execution/ft_free.c \
		./Execution/Builtins/exit.c \
		./Execution/Builtins/unset.c \
		./Execution/Builtins/export_utils.c \
		./Execution/Builtins/env.c \
		./Execution/Builtins/pwd.c \
		./Execution/Builtins/export.c \
		./Execution/Builtins/cd.c \
		./Execution/Builtins/echo.c \
		./Execution/operators.c \
		./Execution/exec_pipe.c \
		./Execution/exec_utils.c \
		./Execution/exec_builtin.c \
		./Execution/toolbox1.c \
		./Parsing/parsing.c \
		./Parsing/syntax_analyzer.c \
		./Parsing/parse_exec.c \
		./Parsing/get_arguments.c \
		./Parsing/broomstick.c \
		./Parsing/null_terminate.c \
		./Parsing/tokenise.c \
		./Parsing/get_arguments_helpers.c \
		./Parsing/syntax_analyzer_helpers.c \
		./Parsing/dollar.c \
		./Parsing/quotes.c \
		./Signals/signals.c \

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

LIB = Libft/libft.a
GNL = Libft/get_next_line/getnextline.a

GREEN = \033[0;32m
NC = \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@make -sC ./Libft
	@$(CC) $(CFLAGS) $(OBJ) $(LIB) $(GNL) -lreadline -o $(NAME)
	@echo -e "$(GREEN)   ___                       ___                       ___           ___           ___           ___       ___ \n     /\__\          ___        /\__\          ___        /\  \         /\__\         /\  \         /\__\     /\__\n    /::|  |        /\  \      /::|  |        /\  \      /::\  \       /:/  /        /::\  \       /:/  /    /:/  /\n   /:|:|  |        \:\  \    /:|:|  |        \:\  \    /:/\ \  \     /:/__/        /:/\:\  \     /:/  /    /:/  / \n  /:/|:|__|__      /::\__\  /:/|:|  |__      /::\__\  _\:\~\ \  \   /::\  \ ___   /::\~\:\  \   /:/  /    /:/  /  \n /:/ |::::\__\  __/:/\/__/ /:/ |:| /\__\  __/:/\/__/ /\ \:\ \ \__\ /:/\:\  /\__\ /:/\:\ \:\__\ /:/__/    /:/__/   \n \/__/~~/:/  / /\/:/  /    \/__|:|/:/  / /\/:/  /    \:\ \:\ \/__/ \/__\:\/:/  / \:\~\:\ \/__/ \:\  \    \:\  \   \n       /:/  /  \::/__/         |:/:/  /  \::/__/      \:\ \:\__\        \::/  /   \:\ \:\__\    \:\  \    \:\  \  \n      /:/  /    \:\__\         |::/  /    \:\__\       \:\/:/  /        /:/  /     \:\ \/__/     \:\  \    \:\  \ \n     /:/  /      \/__/         /:/  /      \/__/        \::/  /        /:/  /       \:\__\        \:\__\    \:\__\ \n     \/__/                     \/__/                     \/__/         \/__/         \/__/         \/__/     \/__/ \nminishell is ready!$(NC)"

clean:
	@rm -f $(OBJ)
	@make clean -sC ./Libft

fclean: clean
	@rm -f $(NAME)
	@make fclean -sC ./Libft

re: fclean all

.PHONY: all clean fclean re
