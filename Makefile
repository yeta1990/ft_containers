SRCS	=	tests/tests.cpp tests/tests_map.cpp tests/tests_more_iterators.cpp tests/tests_reverse_iterator.cpp

OBJS	= $(SRCS:.cpp=.o)

NAME	=	containers_tests

CFLAGS	=	-Wall -Wextra -Werror -std=c++98 --pedantic -g3 -fsanitize=address

RM		=	rm -f

INC		= .

#%.o:%.c
#		$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I$(INC)

$(NAME):	$(OBJS)	
			g++ $(CFLAGS) $(OBJS) -o $(NAME) -I$(INC)

g:	$(OBJS)	
	g++ $(CFLAGS) $(OBJS) -o $(NAME) -I$(INC)

c:	$(OBJS)	
	clang++ $(CFLAGS) $(OBJS) -o $(NAME) -I$(INC)

all:		$(NAME)

clean:
			$(RM) $(OBJS) 

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus
