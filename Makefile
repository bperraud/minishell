SRCS		= minishell.c \
			  utils/utils.c utils/free.c \
			  parsing/parsing.c parsing/init.c \
			  exec/get_path.c \
			  test.c

SRCS		:= $(addprefix src/,$(SRCS))
OBJS		= ${SRCS:.c=.o}
NAME		= minishell
CC			= gcc
MAKE		= make
RM			= rm -f
CFLAGS		= -Wall -Wextra -Werror -Iinclude -Ilibft/include

$(NAME):		$(OBJS)
				$(MAKE) -s -C libft
				$(CC) $(CFLAGS) -lreadline -o $(NAME) $(OBJS) libft/libft.a
all:			$(NAME)
clean:
				$(MAKE) clean -s -C libft
				${RM} ${OBJS}
fclean:			clean
				$(MAKE) fclean -s -C libft
				${RM} $(NAME)
re:				fclean all
.PHONY:			all clean fclean re
.SILENT: 		$(OBJS)