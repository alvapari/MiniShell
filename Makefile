# Librerías
LIBFT = libft/libft.a
FT_PRINTF = ft_printf/libftprintf.a

# Flags
INC = -I /home/achacon-/.brew/Cellar/readline/8.2.13/include
LFLAGS = -L /home/achacon-/.brew/Cellar/readline/8.2.13/lib -lreadline -lncurses
CFLAGS = -Wall -Werror -Wextra
COMPILE = -g

# Colors
GREEN = \033[0;32m
YELLOW = \033[0;93m
FYELLOW = \033[38;5;154m
BLUE = \033[0;96m
PURPLE = \033[0;95m
PINK = \033[0;91m
RED = \033[0;31m
END = \033[0m

# Minishell
NAME = minishell
SRC = src/main.c src/redirs.c src/cmd_list_utils.c src/redir_list_utils.c src/token_list_utils.c src/print_lists.c src/signals.c src/utils.c src/execution.c src/path.c src/ft_echo.c src/ft_cd.c src/ft_env.c src/ft_exit.c src/ft_export.c src/ft_pwd.c src/builtins_utils.c src/ft_unset.c src/parsing_one.c src/parsing_two.c src/parsing_three.c
OBJ_DIR = obj
OBJT = $(SRC:src/%.c=$(OBJ_DIR)/%.o)

# Compilation Rules
$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(OBJ_DIR)
	@gcc ${CFLAGS} ${INC} -c $< -o $@

all: $(NAME)

$(NAME): ${OBJT}
	@echo "$(YELLOW)Compiling Libft.$(END)"
	@make -s -C libft
	@echo "$(GREEN)Libft Compiled.$(END)"
	@echo "$(YELLOW)Compiling Ft_printf.$(END)"
	@make -s -C ft_printf
	@echo "$(GREEN)Ft_printf Compiled.$(END)"
	@echo "$(YELLOW)Compiling Minishell.$(END)"
	@gcc ${CFLAGS} ${OBJT} ${INC} ${LFLAGS} -o ${NAME} ${LIBFT} ${FT_PRINTF}
	@echo "$(GREEN)Minishell Compiled.$(END)"

clean:
	@rm -rf ${OBJ_DIR}
	@make clean -s -C libft
	@make clean -s -C ft_printf
	@echo "$(RED)Compiled objects have been removed.$(END)"

fclean: clean
	@rm -f ${NAME}
	@make fclean -s -C libft
	@make fclean -s -C ft_printf
	@echo "$(RED)Executables objects have been removed.$(END)"

re: fclean all

norminette:
	@echo "$(YELLOW)Norminette libft.$(END)"
	@norminette ./libft
	@echo "$(YELLOW)Norminette ft_printf.$(END)"
	@norminette ./ft_printf
	@echo "$(YELLOW)Norminette minishell.$(END)"
	@norminette ./src