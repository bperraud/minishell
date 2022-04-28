
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/18 01:29:58 by bperraud          #+#    #+#              #
#    Updated: 2022/04/20 00:31:04 by bperraud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC				= minishell.c \
				utils/utils.c utils/free.c \
				parsing/parsing.c parsing/init.c parsing/operators.c parsing/redirections.c\
				exec/get_path.c \
				test.c  \
				pipex/files.c pipex/get_next_line.c pipex/get_next_line_utils.c pipex/pipex.c pipex/utils_pipex.c \
				pipex/split_arg.c pipex/execution.c

TMP				= temp

SRCS			:= $(addprefix src/,$(SRC))
OBJS			= ${SRCS:.c=.o}

NAME			= minishell
CC				= gcc
RM				= rm -f
#CFLAGS			= -Wall -Wextra -Werror -Iinclude -Ilibft/include
CFLAGS			=  -Iinclude -Ilibft/include

all:			tmp $(NAME)

$(NAME):		$(OBJS)
				$(MAKE) -s -C libft
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lreadline libft/libft.a
				make clean

$(ODIR)/%.o: 	$(SRCS)
				$(CC) $(CFLAGS) -c $< -o $@

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
