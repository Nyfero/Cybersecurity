#    Colors
GREY = \e[90m
RED = \e[91m
GREEN = \e[92m
YELLOW = \e[93m
BLUE = \e[34m
PURPLE = \e[95m
CYAN = \e[96m
END = \e[39m

#    Showing command
DISP = TRUE

ifeq ($(DISP),TRUE)
    HIDE =
else
    HIDE = @
endif

#	Includes
INC_PATH = inc

INC = $(addprefix $(INC_PATH)/, ft_otp.hpp)

# LIBS_PATH = ~/Document/in_progress/Parser

CLASS_PATH = class

CLASS_H = $(addprefix $(CLASS_PATH)/,Parser.hpp)

#	Folders
SRCS_PATH = srcs

UTILS_PATH = utils

PARSING_PATH = parsing

#    Files
FILES = main.cpp

# CLASS = $(addprefix $(CLASS_PATH)/, ImageFormat.cpp)

UTILS = $(addprefix $(UTILS_PATH)/, print.cpp)

PARSING = $(addprefix $(PARSING_PATH)/, Parser.cpp check_parsing.cpp)

SRCS = $(addprefix $(SRCS_PATH)/, $(FILES) $(PARSING) $(UTILS))

#    Compilation
NAME = ft_otp

CXX = g++ -std=c++17

CFLAGS = -Wall -Wextra -Werror 

LIBS = 

RM = rm -rf

OBJS_PATH = objs/

OBJS = $(patsubst $(SRCS_PATH)%.cpp $(PARSING_PATH)%.cpp $(UTILS_PATH)%.cpp , $(OBJS_PATH)%.o, $(SRCS))

#    Rules
all: $(NAME)

$(NAME): $(OBJS_PATH) $(OBJS) $(CLASS_H) $(INC)
	@ echo "$(BLUE)\n         ***Make $(NAME) ***\n$(END)"
	$(HIDE) $(CXX) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)
	@ echo "$(GREEN)\n        ---$(NAME) created ---\n$(END)"

$(OBJS_PATH):
	$(HIDE) mkdir -p $(OBJS_PATH)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.cpp $(CLASS_H) Makefile
	$(HIDE) $(CXX) $(CFLAGS) -c $< -o $@
	@ echo "$(GREEN)[ OK ]$(END) $(CYAN)${<:.s=.o}$(END)"

clean:
	$(HIDE) $(RM) $(OBJS_PATH)
	@ echo "$(PURPLE)\n        *** Clean objects ***\n$(END)"

fclean: clean
	$(HIDE) $(RM) $(NAME)
	@ echo "$(RED)\n        *** Remove $(NAME) ***\n$(END)"

re: fclean all

.PHONY: all clean fclean re