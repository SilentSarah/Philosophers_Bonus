# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/28 16:43:35 by hmeftah           #+#    #+#              #
#    Updated: 2023/03/05 17:41:12 by hmeftah          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus
CC = cc
FLAGS = -Wall -Werror -Wextra
INCLUDE = -I Philosophers.h -I /usr/local/include -D_DARWIN_C_SOURCE
SRC = utilities.c dine.c monitor.c utilities_support.c env_builder.c
MAIN = main.c
PTHREAD = -pthread

all: bonus

bonus: $(NAME) $(SRC:.c=.o)

%.o: %.c
	@echo "Building Object File For: |	$< |"
	@$(CC) $(FLAGS) $(PTHREAD) $< -c -o $@

$(NAME): $(SRC:.c=.o) $(MAIN)
	@echo "Building Executables"
	@$(CC) $(FLAGS) $(INCLUDE) $(PTHREAD) $(SRC:.c=.o) $(MAIN) -o $@

clean:
	@echo "Deleting Object Files"
	@rm -rf *.o

fclean: clean
	@echo "Deleting Executables"
	@rm -rf $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re