# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/18 01:29:58 by bperraud          #+#    #+#              #
#    Updated: 2022/04/20 00:19:15 by bperraud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= minishell.c \
			  utils/utils.c utils/free.c \
			  parsing/parsing.c parsing/init.c \
			  exec/get_path.c \
			  test.c \
			  pipex/files.c pipex/get_next_line.c pipex/get_next_line_utils.c pipex/pipex.c pipex/utils_pipex.c pipex/split_arg.c

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

all:			tmp $(NAME)

tmp:
				mkdir -p temp

clean:
				$(MAKE) clean -s -C libft
				${RM} ${OBJS}

fclean:			clean
				$(MAKE) fclean -s -C libft
				${RM} $(NAME)

re:				fclean all

.PHONY:			all clean fclean re

.SILENT: 		$(OBJS)
