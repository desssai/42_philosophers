SRCS	=	sources/philo_bonus_main.c \
			sources/philo_bonus_prep.c \
			sources/philo_bonus_utils.c \


OBJS	=	$(SRCS:.c=.o)

HEADS	=	./includes/

NAME	=	philo_bonus

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