# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/03 22:24:52 by aquinoa           #+#    #+#              #
#    Updated: 2021/04/01 02:29:45 by aquinoa          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a

SRCS		=	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
				ft_isascii.c ft_isdigit.c ft_isprint.c ft_memccpy.c \
				ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
				ft_strchr.c ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
				ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_tolower.c \
				ft_toupper.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
				ft_itoa.c ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c \
				ft_putendl_fd.c ft_putnbr_fd.c ft_itoa_base.c ft_number_len.c \
				ft_array_len.c ft_strrncmp.c ft_isdigit_str.c

SRCS_BONUS	=	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
				ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
				ft_lstmap.c

OBJS		=	$(SRCS:%.c=%.o)

OBJS_BONUS	=	$(SRCS_BONUS:.c=.o)

CFLAGS		=	-Wall -Wextra -Werror

HEADER		=	libft.h

$(NAME):		$(OBJS)
				@ar rc $@ $(OBJS)

all:			$(NAME)

bonus:			$(OBJS) $(OBJS_BONUS)
				@ar rc $(NAME) $(OBJS) $(OBJS_BONUS)

%.o:			%.c $(HEADER)
				@gcc -c $(CFLAGS) $< -I ./$(HEADER)

clean:
				@rm -f $(OBJS) $(OBJS_BONUS)

fclean:			clean
				@rm -f $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
