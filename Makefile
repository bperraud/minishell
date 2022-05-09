# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/30 22:55:34 by bperraud          #+#    #+#              #
#    Updated: 2022/04/30 22:55:34 by bperraud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= minishell.c \
			  utils/utils.c utils/free.c utils/get_next_line.c utils/get_next_line_utils.c \
			  parsing/parsing.c parsing/init.c parsing/redirections.c parsing/operators.c \
			  test.c \
			  pipex/files.c pipex/pipex.c pipex/utils_pipex.c \
			  exec/command.c exec/main_loop.c \
			  buildin/cd.c buildin/echo.c buildin/unset.c

SRCS		:= $(addprefix src/,$(SRCS))
OBJS		= ${SRCS:.c=.o}
NAME		= minishell
CC			= gcc
MAKE		= make
RM			= rm -f
#CFLAGS		= -Wall -Wextra -Werror -Iinclude -Ilibft/include
CFLAGS		= -Iinclude -Ilibft/include

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
