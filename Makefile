
SRCS	=                                                                                            \
		cd.c env.c pwd.c echo.c exit.c main.c unset.c export.c signals.c init_env.c                   \
		env_utils.c make_pipe.c other_func.c processing.c export_utils_1.c export_utils_2.c            \
		lexer.c error.c parser.c no_key.c history.c get_env.c init_all.c init_term.c is_hotkey.c        \
		bonus_key.c move_word.c	parsing_12.c lexer_pipe.c lexer_func.c ft_termcap.c ft_find_in.c         \
		parser_func.c print_utils.c lexer_redir.c parse_if_redir.c key_up_or_down.c signals_termcap.c     \
		parse_if_dollar.c key_home_or_end.c key_left_or_right.c  clear_command_line.c parse_if_quote_one.c \
		parse_if_quote_two.c parse_if_back_redir.c is_special_character.c key_backspace_or_delete.c

NAME		= minishell

LIBFT_PATH	= ./libft

HEADER	= head_minishell.h

CC		= gcc

CFLAGS	= -Wall -Werror -Wextra

OBJS_DIR=	.obj

OBJS	= 	$(addprefix $(OBJS_DIR)/, $(patsubst %.c, %.o, $(SRCS)))

NAME_LOG_FILE	= log.txt



all:	clean_log make_lib $(NAME)

run:	all
		./minishell

make_lib:
			@${MAKE} -C $(LIBFT_PATH)

$(NAME): 	$(OBJS)
			@#$(CC) $(CFLAGS) $(OBJS) -I $(HEADER) $(LIBFT_PATH)/libft.a -ltermcap -o $(NAME)
			@#printf "$(LIGHT_PURPLE)$(BOLD)$(NAME) $(NO_COLOR)–– $(LIGHT_PURPLE)$(BOLD)[Success compiling]        $(NO_COLOR)\n"
			@printf "$(GREEN)$(BOLD)Compiling $(NO_COLOR)$(BOLD)./$(NAME)$(NO_COLOR)$(BOLD):  "
			@$(CC) $(CFLAGS) $(OBJS) -I $(HEADER) $(LIBFT_PATH)/libft.a -ltermcap -o $(NAME) 2>>$(NAME_LOG_FILE) && printf "$(LIGHT_GREEN)$(BOLD)[Success]$(NO_COLOR)\n" && echo > $(NAME_LOG_FILE) || \
            	printf "$(RED)$(BOLD)[Failure]$(NO_COLOR)\nSee 📄 $(BOLD)$(NAME_LOG_FILE)$(NO_COLOR) file for more information.\n"

$(OBJS_DIR)/%.o:	%.c $(HEADER) libft/libft.a Makefile
					@test -d $(OBJS_DIR) || mkdir $(OBJS_DIR)
					@printf "$(GREEN)$(BOLD)Compiling $(UNDER_LINE)$(YELLOW)$<$(NO_COLOR)$(BOLD): wait..."
					@$(CC) $(CFLAGS) -I $(HEADER) -c $< -o $@ 2>>$(NAME_LOG_FILE) && printf "\b\b\b\b\b\b\b       \b\b\b\b\b\b\b" && printf "$(GREEN)[OK]" || \
                    				printf "\b\b\b\b\b\b\b       \b\b\b\b\b\b\b$(RED)[KO]"
					@printf "$(NO_COLOR)\n"

clean_log:
			@echo > $(NAME_LOG_FILE)

clean:		clean_log
			@rm -rf $(OBJS)
			@/bin/rm -rf $(OBJS_DIR)
			@cd $(LIBFT_PATH) && make clean

fclean: 	clean
			@rm -rf $(NAME)
			@cd $(LIBFT_PATH) && make fclean
			@printf "$(BOLD)./$(NAME)$(NO_COLOR) $(LIGHT_RED)deleted$(NO_COLOR)\n"

re: 		fclean all

bonus:
			all

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
