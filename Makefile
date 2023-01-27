NAME = tests_containers
CXX = g++
CXX2 = clang++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 --pedantic -g3 -fsanitize=address
INC = -I. -I../
SRCS = tests/tests.cpp tests/tests_map.cpp tests/tests_more_iterators.cpp tests/tests_reverse_iterator.cpp
OBJS = $(SRCS:.cpp=.o)
RM = rm -f

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@ 

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INC) $(OBJS) -o $@

g: $(OBJS)
	$(CXX) $(CXXFLAGS) $(INC) $(OBJS) -o $@

c: $(OBJS)	
	$(CXX2) $(CXXFLAGS) $(INC) $(OBJS) -o $@

clean:
	$(RM) $(OBJS) 

fclean:	clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
