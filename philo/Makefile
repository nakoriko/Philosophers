# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nakoriko <nakoriko@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/05 20:17:19 by nakoriko          #+#    #+#              #
#    Updated: 2024/11/12 07:50:27 by nakoriko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = fill_struct.c function.c philosofers.c utils.c 

OBJ = $(SRCS:.c=.o)

CC = cc -g

CFLAG = -Wall -Wextra -Werror -fsanitize=thread
LDFLAGS = -lpthread

HEADER = philosophers.h

NAME = philo

all: $(NAME)

$(NAME): $(OBJ) 
	@$(CC) -g $(OBJ) -o $(NAME) $(LDFLAGS)

%.o:%.c $(HEADER)
	@$(CC) $(CFLAG) -c $< -o $@

clean:
	@rm -f $(OBJ)
	
fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY:  all clean fclean re 