# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvalerio <mvalerio@student.42lisboa.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/16 12:37:37 by mvalerio          #+#    #+#              #
#    Updated: 2024/06/23 14:39:13 by mvalerio         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

STANDARD_FLAGS = -Wall -Werror -Wextra -g -pthread #-fsanitize=address

PHILO_LIB = philosophers.a

SRC = \
	src/main.c \
	src/exit.c \
	src/parse_init.c \
	src/utils_1.c \
	src/utils_2.c \
	src/parse_init_mutex.c \
	src/dinner.c \
	src/get_set.c

OBJ = $(SRC:.c=.o)

RED = "\033[31m"
RESET = "\033[0m"
PINK = "\033[35m"
BOLDPINK = "\033[1m\033[35m"
BLINK = "\033[5m"

%.o: %.c
	@$(CC) $(STANDARD_FLAGS) -o $@ -c $<

all: $(NAME)

$(NAME): $(OBJ)
	@echo $(PINK)"Compiling $@"$(RESET)
	@$(CC) $(STANDARD_FLAGS) $(INCLUDE) $(OBJ) -o $(NAME) > /dev/null
	@echo $(BLINK)$(BOLDPINK)"Philosophers are ready to eat!"$(RESET)

$(MINISHELL_LIB): $(OBJ)
	@echo $(PINK)"Creating $@"$(RESET)
	@ar rcs $(PHILO_LIB) $(OBJ)
	@echo $(PINK)The library $(PHILO_LIB) has been created.$(RESET)

clean:
	@rm -f src/*.o
	@echo $(RED)Object files have been deleted.$(RESET)

fclean: clean
	@rm -f $(PHILO_LIB)
	@rm -f $(NAME)
	@echo $(RED)"All created files have been deleted. No philosophers to eat :("$(RESET)

re: fclean all

v: all clean
	@./$(NAME)

.PHONY: fclean clean all re
