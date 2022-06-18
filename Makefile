NAME =	minishell

SRCS =	srcs/main.c\
		srcs/shlvl.c\
		srcs/parser/checks.c\
		srcs/parser/source_parser.c\
		srcs/parser/union_func.c\
		srcs/parser/cleaner.c\
		srcs/parser/parser.c\
		srcs/executor/check_arg_bonus.c\
		srcs/executor/source_executor.c\
		srcs/executor/check_env_bonus.c\
		srcs/executor/erroer_bonus.c\
		srcs/executor/pipex_bonus.c\
		srcs/binary/binary.c\
		srcs/binary/exit.c\
		srcs/binary/cd.c\
		srcs/binary/echo.c\
		srcs/binary/bash.c\
		srcs/binary/export_unset/sorting_export.c\
		srcs/binary/export_unset/export.c\
		srcs/binary/export_unset/unset.c

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS += -Wall -Werror -Wextra -ggdb -fsanitize=address -fno-omit-frame-pointer

#CFLAGS += -g3 -fsanitize=address

RM = rm -rf

LIBFT = libft.a
LIBFTDIR = libft/
LIBFTLINK = -L $(LIBFTDIR) -lft


all:		$(NAME)

$(NAME):	complib $(OBJS) echoOK
	@$(CC) $(CFLAGS) -o $@ $(OBJS) -I./include -lreadline $(LIBFTLINK)

complib:
	@$(MAKE) -C libft/

%.o:		%.c
	@$(CC) -c $(CFLAGS) -o $@ $<
	printf "$(GREEN)██"

clean: echoCLEAN
	@$(MAKE) -C $(LIBFTDIR) clean
	@$(RM) $(OBJS)

fclean: clean echoFCLEAN
	@$(MAKE) -C $(LIBFTDIR) fclean
	@$(RM) $(OBJS)
	@$(RM) $(NAME)

re:		fclean all

leaks:
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(NAME)

norm:
	norminette ./srcs/* ./libft/*

.PHONY:		all clean fclean re leaks norm
.SILENT:

##############______________Colors______________##############

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
CYAN = \033[1;36m
END = \033[0m

##############______________MESSAGES______________##############

echoOK:
	echo "$(GREEN) Compiling$(END)\n"
echoCLEAN :
	echo "\n$(RED)Clean$(END)"
echoFCLEAN :
	echo "$(RED)Fclean$(END)\n"
