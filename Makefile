SRCS		= minishell.c \
			  utils/utils.c utils/free.c utils/get_next_line.c utils/get_next_line_utils.c \
			  parsing/parsing.c parsing/init.c parsing/redirections.c parsing/operators.c \
			  test.c \
			  pipex/files.c pipex/pipex.c pipex/utils_pipex.c pipex/split_arg.c pipex/execution.c
SRCS		:= $(addprefix src/,$(SRCS))
OBJS		= ${SRCS:.c=.o}
NAME		= minishell
CC			= gcc
MAKE		= make
RM			= rm -f
CFLAGS		= -Wall -Wextra -Werror -Iinclude -Ilibft/include

$(NAME):		$(OBJS)
				$(MAKE) -s -C libft
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lreadline libft/libft.a
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
