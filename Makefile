SRCS		= minishell.c
SRCS		:= $(addprefix src/,$(SRCS))
OBJS		= ${SRCS:.c=.o}
NAME		= minishell
CC			= gcc
MAKE		= make
RM			= rm -f
CFLAGS		= -Wall -Wextra -Werror -Iinclude -Ilibft/include -fsanitize=address

$(NAME):		$(OBJS)
				$(MAKE) -C libft
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) libft/libft.a
all:			$(NAME)
clean:
				$(MAKE) clean -C libft
				${RM} ${OBJS}
fclean:			clean
				$(MAKE) fclean -C libft
				${RM} $(NAME)
re:				fclean all
.PHONY:			all clean fclean re