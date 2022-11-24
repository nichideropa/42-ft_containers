NAME			:=	ft_containers

RM				:= rm -rf
CXX				:= c++
CPPFLAGS		:= -std=c++98 #-Wall -Werror -Wextra
# -pedantic flagged color codes because not iso standard

SRCS			:= 	main.cpp
OBJS			:= 	$(SRCS:%.cpp=%.o)
DEPS			:= 	$(OBJS:%.o=%.d)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CPPFLAGS) -o $(NAME) $(OBJS)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -MMD -MP -c $< -o $@

$(DEPS):

clean:
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

-include $(DEPS)
