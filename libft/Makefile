
SRCS	=                                                                    \
		ft_atoi.c ft_itoa.c ft_bzero.c ft_split.c ft_calloc.c ft_memchr.c     \
		ft_memcmp.c ft_memcpy.c ft_strlen.c ft_strdup.c ft_substr.c            \
		ft_strchr.c ft_memset.c ft_isalnum.c ft_isalpha.c ft_isascii.c          \
		ft_strmapi.c ft_isdigit.c ft_isprint.c ft_memccpy.c ft_memmove.c         \
		ft_strlcat.c ft_strlcpy.c ft_strncmp.c ft_strnstr.c ft_strrchr.c          \
		ft_tolower.c ft_toupper.c ft_strjoin.c ft_strtrim.c ft_strrncmp.c          \
		ft_putstr_fd.c ft_putnbr_fd.c ft_itoa_base.c ft_array_len.c ft_putchar_fd.c \
		ft_putendl_fd.c ft_number_len.c ft_isdigit_str.c ft_lstnew.c ft_lstmap.c     \
		ft_lstsize.c ft_lstiter.c ft_lstlast.c ft_lstclear.c ft_lstdelone.c           \
		ft_lstadd_back.c ft_lstadd_front.c ft_strjoin_char.c ft_strjoin_free.c         \
		ft_strdup_free.c ft_char_to_str.c get_next_line.c get_next_line_utils.c

NAME	= libft.a

HEADER	= libft.h

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

OBJS_DIR= .obj

OBJS	= $(addprefix $(OBJS_DIR)/, $(patsubst %.c, %.o, $(SRCS)))



all:	$(NAME)

$(NAME):	$(OBJS)
			@printf "$(GREEN)$(BOLD)Compiling $(NO_COLOR)$(BOLD)$(NAME)$(NO_COLOR)$(BOLD):  "
			@ar rc $(NAME) $? && printf "$(GREEN)$(BOLD)[Success]$(NO_COLOR)\n" || \
            printf "$(RED)$(BOLD)[Failure]$(NO_COLOR)\n"

$(OBJS_DIR)/%.o:	%.c $(HEADER) Makefile
				@test -d $(OBJS_DIR) || mkdir $(OBJS_DIR)
				@printf "$(GREEN)$(BOLD)Compiling $(UNDER_LINE)$(YELLOW)$<$(NO_COLOR)$(BOLD): wait..."
				@$(CC) $(CFLAGS) -c $< -o $@ && printf "\b\b\b\b\b\b\b       \b\b\b\b\b\b\b$(GREEN)[OK] $(NO_COLOR)\n" || \
				printf "\b\b\b\b\b\b\b       \b\b\b\b\b\b\b$(RED)[KO]$(NO_COLOR)\n"

clean:
		@rm -rf $(OBJS)
		@/bin/rm -rf $(OBJS_DIR)

fclean: clean
		@rm -rf $(NAME)
		@printf "$(BOLD)$(NAME)$(NO_COLOR)$(LIGHT_RED) deleted$(NO_COLOR)\n"

re: 	fclean all

################
##   COLORS   ##
################

UNDER_LINE	= \033[4m
NO_COLOR 	= \033[0m
BOLD	 	= \033[1m
RED 	 	= \033[0;31m
GREEN 	 	= \033[0;32m
LIGHT_RED	= \033[1;31m
YELLOW 		= \033[1;33m
LIGHT_PURPLE= \033[1;35m
WHITE 		= \033[1;37m

.PHONY:	all clean fclean re
.PHONY: SRCS NAME HEADER CC CFLAGS OBJS_DIR OBJS
.PHONY: UNDER_LINE BOLD NO_COLOR RED GREEN LIGHT_RED YELLOW LIGHT_PURPLE WHITE
