RED			=	"\033[0;31m"
GREEN		=	"\033[0;32m"
YELLOW		=	"\033[0;33m"
WHITE		=	"\033[0;37m"
ENDCOLOR	=	"\033[0;0m"
LINE_CLEAR	=	"\x1b[1A\x1b[M"

CXX = c++
CXXFLAGS = -I./include -I./include/cmds -I./include/server -I./include/utils -Wall -Wextra -Werror -std=c++98 #-g -fsanitize=address
RM = rm -rf
NAME = canServ.out

SRCS_DIR = ./srcs
DIR_CMDS = $(SRCS_DIR)/cmds
DIR_SERVER = $(SRCS_DIR)/server

#$(wildcard ./srcs/cmds/*.cpp)
SRCS_CMDS	:=	ACommand.cpp Join.cpp Kick.cpp Nick.cpp Notice.cpp \
				Part.cpp Pass.cpp Ping.cpp Prvmsg.cpp \
				Quit.cpp User.cpp Bot.cpp
SRCS_CMDS	:=	$(addprefix $(DIR_CMDS)/, $(SRCS_CMDS))

# $(wildcard ./srcs/server/*.cpp)
SRCS_SERVER	:=	CanChannel.cpp CanClient.cpp CanException.cpp CanServer.cpp \
				Operation.cpp Utility.cpp Parsing.cpp
SRCS_SERVER	:=	$(addprefix $(DIR_SERVER)/, $(SRCS_SERVER))

SRCS		=	./srcs/main.cpp $(SRCS_CMDS) $(SRCS_SERVER) 

OBJS		=	$(SRCS:.cpp=.o)

$(NAME) : $(OBJS) 
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o		:	%.cpp
	$(CXX) $(CXXFLAGS) -c $<  -o $@

all : $(NAME)

clean :
	@echo $(YELLOW) "🍪 Cleaning Object file..." $(ENDCOLOR)
	$(RM) $(OBJS)
	@echo $(RED) "🍪 Object files cleaned!" $(ENDCOLOR)

fclean : clean
	@echo $(YELLOW) "🍪 Cleaning Object & Program file..." $(ENDCOLOR)
	$(RM) -f $(NAME)
	@echo $(RED) "🍪 $(NAME) is removed!" $(ENDCOLOR)

re : 
	@echo $(YELLOW) "🍪 make re!" $(ENDCOLOR)
	$(MAKE) fclean 
	$(MAKE) all
	@echo $(RED) "🍪 make re finished!" $(ENDCOLOR)

.PHONY : all clean fclean bonus re