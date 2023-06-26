# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/24 14:27:20 by cmansey           #+#    #+#              #
#    Updated: 2023/06/26 12:20:30 by cmansey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = minishell.c

OBJ := $(SRC:%.c=%.o)

CC = gcc
RM = rm -f
CFLAGS = -Wextra -Wall -Werror
INCLUDES = -Iincludes
LIBRARIES = -Llibft -lft -lreadline
LIBFT = libft

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $^ $(LIBRARIES) -o $(NAME)

debug: $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -fsanitize=address $^ $(LIBRARIES) -o $(NAME)

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
