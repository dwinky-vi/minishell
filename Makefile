
SRCS	= \
		main.c \
		processing.c echo.c pwd.c cd.c env.c other_func.c unset.c export.c exit.c init_env.c \
		env_utils.c pipe_n_redir.c signals.c \
		parser.c print_utils.c init_term.c get_env.c \
		key_left_right.c key_home_or_end.c key_backspace_or_delete.c move_word.c history.c \
		parse_if_dollar.c parse_if_quote_one.c is_hotkey.c clear_command_line.c error.c \
		lexer.c lexer_redir.c lexer_pipe.c lexer_func.c

NAME		= minishell

LIBFT_PATH	= ./libft

HEADER		= head_minishell.h

CC		= gcc

CFLAGS	= -g

# создаём скрытую директорию, в которой будут .o файлы
OBJS_DIR =	.obj

# VPATH = *перечесление папок*

# прописываем (добавляем) путь для каждого .o файла
OBJS	= 	$(addprefix $(OBJS_DIR)/, $(patsubst %.c, %.o, $(SRCS)))

NORM 	=	norminette

all:		make_lib $(NAME)

run:	all
		./minishell

make_lib:
			@${MAKE} -C $(LIBFT_PATH)

$(NAME): 	$(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) -I $(HEADER) $(LIBFT_PATH)/libft.a -ltermcap -o $(NAME)
			@printf "$(LIGHT_PURPLE)$(BOLD)$(NAME) $(NO_COLOR)–– $(LIGHT_PURPLE)$(BOLD)[Success compiling]        $(NO_COLOR)\n"

$(OBJS_DIR)/%.o:	%.c $(HEADER) libft/libft.a
					@test -d $(OBJS_DIR) || mkdir $(OBJS_DIR)
					@printf "$(GREEN)$(BOLD)Compilation $(UNDER_LINE)$(YELLOW)$<$(NO_COLOR)  $(BOLD)–– $(RED)[KO]        $(NO_COLOR)\r"
					@$(CC) $(CFLAGS) -I $(HEADER) -c $< -o $@
					@printf "$(GREEN)$(BOLD)Compilation $(UNDER_LINE)$(YELLOW)$<$(NO_COLOR)  $(BOLD)–– $(GREEN)[OK]$(NO_COLOR)\n"

clean:
			@rm -rf $(OBJS)
			@/bin/rm -rf $(OBJS_DIR)
			@cd $(LIBFT_PATH) && make clean

fclean: 	clean
			@rm -rf $(NAME)
			@cd $(LIBFT_PATH) && make fclean
			@printf "$(UNDER_LINE)$(BOLD)$(NAME)$(NO_COLOR) $(LIGHT_RED)deleted$(NO_COLOR)\n"

re: 		fclean all

norm:
			@$(NORM) $(SRCS) $(HEADER)
			@cd $(LIBFT_PATH) && make norm

################
##   COLORS   ##
################

UNDER_LINE	= \033[4m
BOLD	 	= \033[1m

NO_COLOR 	= \033[0m
BLACK	 	= \033[0;30m
RED 	 	= \033[0;31m
GREEN 	 	= \033[0;32m
BROWN 	 	= \033[0;33m
BLUE 		= \033[0;34m
PURPLE 	 	= \033[0;35m
CYAN 	 	= \033[0;36m
LIGHT_GRAY	= \033[0;37m

DARK_GRAY	= \033[1;30m
LIGHT_RED	= \033[1;31m
LIGHT_GREEN	= \033[1;32m
YELLOW 		= \033[1;33m
LIGHT_BLUE	= \033[1;34m
LIGHT_PURPLE= \033[1;35m
LIGHT_CYAN	= \033[1;36m
WHITE 		= \033[1;37m

.PHONY:	all clean fclean re
.PHONY: make_lib norm
.PHONY: SRCS NAME LIBFT_PATH HEADER CC CFLAGS OBJS_DIR OBJS NORM
.PHONY: UNDER_LINE BOLD NO_COLOR BLACK RED GREEN BROWN BLUE PURPLE CYAN LIGHT_GRAY DARK_GRAY LIGHT_RED LIGHT_GREEN YELLOW LIGTH_BLUE LIGHT_PURPLE LIGHT_CYAN WHITE
