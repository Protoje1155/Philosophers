# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkoster <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/12 18:16:17 by mkoster           #+#    #+#              #
#    Updated: 2024/06/25 15:06:21 by mkoster          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
SRCS_DIR = src
SRCS = helper_functions.c philo.c init.c error_handling.c \
	threads_func.c time.c eat.c get_set.c synchro.c sleep.c safe_mutexes.c
OBJS = $(SRCS:.c=.o)
CC = cc
YELLOW := "\033[0;33m"
GREEN := "\033[0;32m"
BLUE := "\033[0;34m"
RED := "\033[0;31m"
NC := "\033[0m"
CFLAGS = -Werror -Wall -Wextra -pthread
NAME = philo

all: $(NAME)

$(NAME): $(OBJS) $(PRINTF_LIB)
	@echo $(GREEN)"Compiling $(NAME)..."$(NC)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	@echo $(YELLOW)"Compiling $<"$(NC)
	@$(CC) $(CFLAGS) -c $< -o $@


clean:
	@echo $(RED)"Cleaning objects..."$(NC)
	@rm -rf $(OBJS)

fclean: clean
	@echo $(BLUE)"Cleaning $(NAME)..."$(NC)
	@rm -rf $(NAME)
	
re: fclean all

.PHONY: all philo clean fclean re
