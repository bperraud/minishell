SRCS		= minishell.c test.c \
			  utils/utils.c utils/free.c utils/get_next_line.c utils/get_next_line_utils.c \
			  utils/prompt.c utils/shell_utils.c utils/list.c utils/env.c utils/env_utils.c \
			  parsing/parsing.c parsing/init.c parsing/redirections.c parsing/operators.c \
			  parsing/error.c \
			  pipex/files.c pipex/pipex.c pipex/utils_pipex.c pipex/list_cmd.c \
			  exec/command.c exec/main_loop.c \
			  builtin/cd.c builtin/echo.c builtin/export.c builtin/unset.c builtin/env.c builtin/pwd.c builtin/exit.c

SRCS		:= $(addprefix src/,$(SRCS))
OBJS		= ${SRCS:.c=.o}
NAME		= minishell
CC			= gcc
MAKE		= make
RM			= rm -f
CFLAGS		+= -Wall -Wextra -Werror -Iinclude -Ilibft/include -g
LFLAGS		+= -lreadline libft/libft.a

$(NAME):		$(OBJS)
				$(MAKE) -s -C libft
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lreadline libft/libft.a
				${RM} ${OBJS}

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
