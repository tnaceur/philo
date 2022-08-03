NAME = philo
CFLAG = -Wall -Wextra -Werror -g -fsanitize=thread
CC = gcc
SRCS = philo.c\

RM = rm -rf
OBJ = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
		   $(CC) $(CFLAG) $(OBJ) -o $(NAME)

clean :
		$(RM) $(OBJ)

fclean : clean
		 $(RM) $(NAME)
re : fclean all