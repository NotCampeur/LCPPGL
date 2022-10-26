# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/12 20:05:44 by ldutriez          #+#    #+#              #
#    Updated: 2022/10/26 15:48:45 by ldutriez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=		liblcppgl

CC 		=		c++

SRC_DIR = 		$(shell find srcs -type d)
INC_DIR = 		$(shell find includes -type d) \
				$(shell find srcs -type d)

OBJ_DIR = 		objs

vpath %.cpp $(foreach dir, $(SRC_DIR), $(dir):)

TOOLS	=		Rectangle.cpp Color.cpp Texture.cpp \
				basic_functions.cpp Vector3.cpp

SYSTEM	=		Application.cpp Context.cpp

RENDER	=		Printer.cpp ZPrinter.cpp Writer.cpp

SRC 	=		${SYSTEM} \
				${RENDER} \
				${TOOLS}

TEST_SRC =		test.cpp 3dtest.cpp \
				${SRC}

OBJ		=		$(addprefix $(OBJ_DIR)/, $(SRC:%.cpp=%.o))
TEST_OBJ = 		$(addprefix $(OBJ_DIR)/, $(TEST_SRC:%.cpp=%.o))
#Compilation flag
CFLAGS	=		-Wall -Wextra -Werror 

# Colors

_GREY=	$'\033[30m
_RED=	$'\033[31m
_GREEN=	$'\033[32m
_YELLOW=$'\033[33m
_BLUE=	$'\033[34m
_PURPLE=$'\033[35m
_CYAN=	$'\033[36m
_WHITE=	$'\033[37m

DEBUG =
# Add fsanitize to the compilation flags if DEBUG is set to fs.
# If DEBUG is set to valgrind, add debug flags to the compilation flags.
ifeq ($(DEBUG), fs)
	CFLAGS += -fsanitize=address
	CFLAGS += -g3
	CFLAGS += -O0
	msg = $(shell echo "$(_PURPLE)fsanitize and debug flags are added.$(_WHITE)")
	useless := $(info $(msg))
else ifeq ($(DEBUG), vl)
	CFLAGS += -g3
	CFLAGS += -O0
	msg = $(shell echo "$(_PURPLE)Valgrind and debug flags are added. Take care to rebuild the program entirely if you already used valgrind.$(_WHITE)")
	useless := $(info $(msg))
else ifeq ($(DEBUG), gdb)
	CFLAGS += -g3
	CFLAGS += -O0
	msg = $(shell echo "$(_PURPLE)gdb and debug flags are added.$(_WHITE)")
	useless := $(info $(msg))
else
	CFLAGS += -O3
	msg = $(shell echo "$(_PURPLE)Debug mode not enabled. Optimization flags are added.$(_WHITE)")
	useless := $(info $(msg))
endif

#Include flag
IFLAGS	=		$(foreach dir, $(INC_DIR), -I$(dir))

print-%  : ; @echo $* = $($*)

SDL = ./ressources/great.png

all:			$(SDL) $(NAME).a

$(NAME).a:		$(OBJ) Makefile
				@echo "-----\nCompiling $(_YELLOW)$@$(_WHITE) ... \c"
				@ar rc $@ $(OBJ)
				@ranlib $@
				@echo "$(_GREEN)DONE$(_WHITE)\n-----"
				
$(SDL):
				@./ressources/installing_SDL2.sh

test:			$(NAME).a $(TEST_OBJ)
				@echo "-----\nTesting $(_YELLOW)$(NAME)$(_WHITE) ... \c"
				@$(CC) $(CFLAGS) $(IFLAGS) $(TEST_OBJ) `sdl2-config --libs` -lSDL2_ttf -lSDL2_image $< -o $(NAME)
				@./$(NAME)
				@echo "$(_GREEN)DONE$(_WHITE)\n-----"

show:
				@echo "\nSRC :\n$(SRC)\n"
				@echo "OBJ :\n$(OBJ)\n"
				@echo "CFLAGS :\n$(CFLAGS)\n"
				@echo "IFLAGS :\n$(IFLAGS)\n"
				@echo "LIB_DIR :\n$(LIB_DIR)\n"

$(OBJ_DIR)/%.o : 	%.cpp
				@echo "Compiling $(_YELLOW)$@$(_WHITE) ... \c"
				@mkdir -p $(OBJ_DIR)
				@$(CC) $(CFLAGS) $(IFLAGS) `sdl2-config --cflags` -o $@ -c $<
				@echo "$(_GREEN)DONE$(_WHITE)"

re:				fclean all

clean:
				@echo "Deleting Objects Directory $(_YELLOW)$(OBJ_DIR)$(_WHITE) ... \c"
				@rm -rf $(OBJ_DIR)
				@echo "$(_GREEN)DONE$(_WHITE)\n-----"

fclean:			clean
				@echo "Deleting library File $(_YELLOW)$(NAME).a $(_WHITE)and executable $(_YELLOW)$(NAME)$(_WHITE) ... \c"
				@rm -f $(NAME) $(NAME).a
				@echo "$(_GREEN)DONE$(_WHITE)\n-----"

.PHONY:			all show re clean fclean test