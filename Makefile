# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/07 19:11:22 by hporta-c          #+#    #+#              #
#    Updated: 2025/07/23 14:47:12 by hporta-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT_DIR = libft
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR)

LIBFT = $(LIBFT_DIR)/libft.a
LIB = -lreadline

SRCS = main.c command_list.c variable_list.c tokenize.c extract_cmd_args.c \
		variable_value.c extract_cmd_args_by_quote.c dollar_sign.c \
		utils_str.c tokenize_utils.c variable_utils.c dollar_sign_utils.c
OBJS = $(SRCS:.c=.o)

RM = rm -f

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIB) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: fclean clean all re