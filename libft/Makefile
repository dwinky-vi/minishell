
SRCS	= \
		ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
		ft_isascii.c ft_isdigit.c ft_isprint.c ft_memccpy.c \
		ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
		ft_strchr.c ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
		ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_tolower.c \
		ft_toupper.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
		ft_itoa.c ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c \
		ft_putendl_fd.c ft_putnbr_fd.c ft_itoa_base.c ft_number_len.c \
		ft_array_len.c ft_strrncmp.c ft_isdigit_str.c \
		ft_lstnew.c ft_lstsize.c ft_lstlast.c ft_lstadd_front.c ft_lstadd_back.c \
		ft_lstiter.c ft_lstdelone.c ft_lstclear.c ft_lstmap.c

NAME	= libft.a

HEADER	= libft.h

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

# about other flags
# -Wfloat-equal выдаст ошибку при сравнении чисел с плавующей точкой
# -Wundef предупреждать, если неинициализированный идентификатор оценивается в случае
# -Wconversion неявное приведение типов
#  -ftrapv переполнение целовего числа
# -Wunreachable-code # 

# создаём скрытую директорию, в которой будут .o файлы
OBJS_DIR =			.obj

# прописываем (добавляем) путь для каждого .o файла
OBJS	= 			$(addprefix $(OBJS_DIR)/, $(patsubst %.c, %.o, $(SRCS)))

NORM 	=			~/.scripts/colorised_norm.sh

all:		$(NAME)

$(NAME): 	$(OBJS)
			@ar rc $(NAME) $?
			@printf "$(GREEN)$(BOLD)$(LIGHT_PURPLE)libft –– [Success compiling]        $(NO_COLOR)\n"

$(OBJS_DIR)/%.o:	%.c $(HEADER)
					@test -d $(OBJS_DIR) || mkdir $(OBJS_DIR)
					@printf "$(GREEN)$(BOLD)Compilation $(UNDER_LINE)$(YELLOW)$<$(NO_COLOR)  $(BOLD)–– $(RED)[KO]        $(NO_COLOR)\r"
					@$(CC) $(CFLAGS) -c $< -o $@
					@printf "$(GREEN)$(BOLD)Compilation $(UNDER_LINE)$(YELLOW)$<$(NO_COLOR)  $(BOLD)–– $(GREEN)[OK]$(NO_COLOR)\n"

clean:
			@rm -rf $(OBJS)
			@/bin/rm -rf $(OBJS_DIR)

fclean: 	clean
			@rm -rf $(NAME)
			@printf "$(UNDER_LINE)$(BOLD)$(NAME)$(NO_COLOR) $(LIGHT_RED)  deleted$(NO_COLOR)\n"

re: 		fclean all

norm:		
			@$(NORM) $(SRCS) $(HEADER)

################
##   COLORS   ##
################

UNDER_LINE	= \033[4m
BOLD	 	= \033[1m
NO_COLOR 	= \033[0m
RED 	 	= \033[0;31m
GREEN 	 	= \033[0;32m
LIGHT_RED	= \033[1;31m
YELLOW 		= \033[1;33m
LIGHT_PURPLE= \033[1;35m
WHITE 		= \033[1;37m

.PHONY:	all clean fclean re norm
.PHONY: SRCS NAME HEADER CC CFLAGS OBJS_DIR OBJS NORM
.PHONY: UNDER_LINE BOLD NO_COLOR RED GREEN LIGHT_RED YELLOW LIGHT_PURPLE WHITE
