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

LIBS_PATH = /mnt/nfs/homes/gsap/Documents/in_progress/Parser

#	Folders
SRCS_PATH = srcs

GENERATE_PATH = generate

PARSING_PATH = parsing

STORE_PATH = store

UTILS_PATH = utils

#    Files
FILES = main.cpp

GENERATE = $(addprefix $(GENERATE_PATH)/, checkKey.cpp generateCode.cpp)

PARSING = $(addprefix $(PARSING_PATH)/, checkParsing.cpp)

STORE = $(addprefix $(STORE_PATH)/, checkHexa.cpp storeKey.cpp)

UTILS = $(addprefix $(UTILS_PATH)/, print.cpp encrypted.cpp decrypted.cpp)

SRCS = $(addprefix $(SRCS_PATH)/, $(FILES) $(GENERATE) $(PARSING) $(STORE) $(UTILS))

#    Compilation
NAME = ft_otp

CXX = g++ -std=c++17

CFLAGS = -Wall -Wextra -Werror

LIBS = -L$(LIBS_PATH) -lParser -lssl -lcrypto

RM = rm -rf

OBJS_PATH = objs/

OBJS = $(patsubst $(SRCS_PATH)%.cpp $(GENERATE_PATH)%.cpp $(PARSING_PATH)%.cpp $(STORE_PATH)%.cpp $(UTILS_PATH)%.cpp , $(OBJS_PATH)%.o, $(SRCS))

#    Rules
all: $(NAME)

$(NAME): $(OBJS_PATH) $(OBJS) $(CLASS_H) $(INC)
	@ echo "$(BLUE)\n         ***Make $(NAME) ***\n$(END)"
	$(HIDE) $(CXX) $(CFLAGS) -I$(LIBS_PATH) $(OBJS) -o $(NAME) $(LIBS)
	@ echo "$(GREEN)\n        ---$(NAME) created ---\n$(END)"

$(OBJS_PATH):
	$(HIDE) mkdir -p $(OBJS_PATH)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.cpp $(CLASS_H) Makefile
	$(HIDE) $(CXX) $(CFLAGS) -I$(LIBS_PATH) -c $< -o $@
	@ echo "$(GREEN)[ OK ]$(END) $(CYAN)${<:.s=.o}$(END)"

clean:
	$(HIDE) $(RM) $(OBJS_PATH)
	@ echo "$(PURPLE)\n        *** Clean objects ***\n$(END)"

fclean: clean
	$(HIDE) $(RM) $(NAME)
	@ echo "$(RED)\n        *** Remove $(NAME) ***\n$(END)"

re: fclean all

.PHONY: all clean fclean re