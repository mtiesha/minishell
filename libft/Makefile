# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/10 12:54:23 by mtiesha           #+#    #+#              #
#    Updated: 2022/06/29 10:12:49 by mtiesha          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = 	ft_atoi.c		ft_bzero.c		ft_calloc.c \
		ft_isalnum.c	ft_isalpha.c	ft_isascii.c \
		ft_isdigit.c	ft_isprint.c	ft_isspase.c \
		ft_memchr.c		ft_memcmp.c		ft_memcpy.c \
		ft_memmove.c	ft_memset.c		ft_putchar_fd.c \
		ft_putendl_fd.c	ft_putnbr_fd.c	ft_putstr_fd.c \
		ft_split.c		ft_strchr.c		ft_strdup.c \
		ft_striteri.c	ft_strjoin.c	ft_strlcat.c \
		ft_strlcpy.c	ft_strlen.c		ft_strmapi.c \
		ft_strncmp.c	ft_strnstr.c	ft_strrchr.c \
		ft_strtrim.c	ft_substr.c		ft_tolower.c \
		ft_toupper.c	ft_splitutils.c	ft_isutils.c \
		ft_swap.c		ft_strndup.c	ft_itoa.c \
		ft_get_next_line.c	ft_get_func.c	ft_double.c \
		ft_char.c		ft_free_func.c

SRCS_B = ft_lstnew_bonus.c	ft_lstadd_front_bonus.c \
		ft_lstsize_bonus.c	ft_lstlast_bonus.c

RM = rm -f

CFLAGS = -Wall -Wextra -Werror

LIB = ar rcs

OBJ = ${SRCS:.c=.o}

OBJ_B = ${SRCS_B:.c=.o}

CC = gcc

all : ${NAME}

${NAME} : ${OBJ} Makefile libft.h
	@${LIB} ${NAME} ${OBJ}
	@echo "\033[1;36mlibft.a created"

${OBJ} : ${SRCS} Makefile libft.h
	@${CC} ${CFLAGS} ${SRCS} -c -I.

bonus : ${OBJ_B} Makefile libft.h
	@${LIB} ${NAME} ${OBJ_B}

${OBJ_B} : ${SRCS_B} Makefile libft.h
	@${CC} ${CFLAGS} ${SRCS_B} -c -I.

clean :
	@${RM} ${OBJ} ${OBJ_B}
	@echo "\033[1;36mlibft Clean"

fclean : clean
	@${RM} ${NAME}
	@echo "\033[1;36mlibft Fclean"

re : fclean all

.PHONY : clean fclean all re bonus
