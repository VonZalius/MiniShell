# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/24 14:27:20 by cmansey           #+#    #+#              #
#    Updated: 2023/09/28 14:32:05 by cmansey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = $(wildcard *.c) $(wildcard executor/*.c)

OBJ := $(SRC:%.c=%.o)

CC = gcc
RM = rm -f
CFLAGS = -Wextra -Wall -Werror
INCLUDES = -Iincludes
LIBRARIES = -Llibft -lft -lreadline -L/Users/abarras/.brew/opt/readline/lib -I/Users/abarras/.brew/opt/readline/include
LIBFT = libft

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $^ $(LIBRARIES) -o $(NAME)

debug: $(OBJ)
	@make -C $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) -fsanitize=address -fno-omit-frame-pointer $^ $(LIBRARIES) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ): %.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJ)
	@make clean -C $(LIBFT)

fclean: clean
	make clean
	$(RM) $(NAME)
	@$(RM) -f $(LIBFT)/libft.a

re: fclean all

.PHONY: all clean fclean re libft
