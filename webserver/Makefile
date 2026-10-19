NAME		:= webserv
 
CXX			:= c++
CXXFLAGS	:= -Wall -Wextra -Werror -std=c++98
DEPFLAGS	:= -MMD -MP
INCLUDES	:= -Iinclude
 
SRC_DIR		:= src
OBJ_DIR		:= obj
 
SRCS		:= src/main.cpp \
			   src/config.cpp \
			   src/configparser.cpp \
			   src/connection.cpp \
			   src/request.cpp \
			   src/server.cpp \
			   src/multipart.cpp 
OBJS		:= $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEPS		:= $(OBJS:.o=.d)
 
RM			:= rm -rf
 
all: $(NAME)
 
$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
 
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) $(INCLUDES) -c $< -o $@
 
clean:
	$(RM) $(OBJ_DIR)
 
fclean: clean
	$(RM) $(NAME)
 
re: fclean all
 
-include $(DEPS)
 
.PHONY: all clean fclean re