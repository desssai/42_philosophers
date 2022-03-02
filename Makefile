SRCS	=	sources/philo_main.c \
			sources/philo_prep.c \
			sources/philo_utils.c \


OBJS	=	$(SRCS:.c=.o)

HEADS	=	./includes/

NAME	=	philo

GCC		=	gcc

FLAGS	=	-Wall -Werror -Wextra

RM		=	rm -f

%.o: %.c ./includes/philo.h
	$(GCC) $(FLAGS) -I$(HEADS) -c $< -o $@ 

$(NAME): $(OBJS)
	$(GCC) $(FLAGS) $(OBJS) -o $(NAME) 

all:	$(NAME)

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(LNAME)
		$(RM) $(NAME)

re:		fclean all