# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/28 17:57:20 by mtiesha           #+#    #+#              #
#    Updated: 2022/06/28 17:57:20 by mtiesha          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	minishell

SRCS =	srcs/main.c	srcs/signal.c\
		srcs/lexer/support.c	srcs/lexer/redirecter.c\
		srcs/lexer/dollar_opener.c	srcs/lexer/file_opener.c\
		srcs/lexer/lexer.c	srcs/parser/checks.c\
		srcs/parser/source_parser.c	srcs/parser/union_func.c\
		srcs/parser/cleaner.c	srcs/parser/redirect.c\
		srcs/parser/parser.c	srcs/executor/open_files.c\
		srcs/executor/check_arg_bonus.c	srcs/executor/source_executor.c\
		srcs/executor/check_env_bonus.c	srcs/executor/erroer_bonus.c\
		srcs/executor/here_doc.c	srcs/executor/pipex_bonus.c\
		srcs/binary/binary.c	srcs/binary/exit.c\
		srcs/binary/cd.c	srcs/binary/echo.c\
		srcs/binary/bash.c\
		srcs/binary/export_unset/sorting_export.c	srcs/binary/export_unset/export.c\
		srcs/binary/export_unset/unset.c

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra

#CFLAGS += -ggdb -fsanitize=address -fsanitize=leak -fno-omit-frame-pointer

LIBFT = libft/libft.a
LINKLIB = -L libft/ -lft

RM = rm -rf

all : $(NAME)

$(NAME) : $(OBJS) ${LIBFT}
	@$(CC) $(CFLAGS) -o $@ $(OBJS) -I./include -lreadline $(LINKLIB)
	@echo ""
	@echo "\033[1;32mCompiled"

%.o : %.c ${LIBFT} Makefile ./include/minishell.h
	@$(CC) -c $(CFLAGS) -o $@ $<
	@echo -n "\033[1;35m♥"

${LIBFT} : ./libft/Makefile ./libft/libft.h ./libft/*.c
	@$(MAKE) all -C libft/

clean :
	@$(MAKE) clean -C libft/
	@$(RM) $(OBJS)
	@echo "\033[1;31mMinishell Clean"

fclean : clean
	@$(MAKE) fclean -C libft/
	@$(RM) $(NAME)
	@echo "\033[1;31mMinishell Fclean"

re : fclean all

.PHONY : all clean fclean re
