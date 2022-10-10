# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/12 20:05:44 by ldutriez          #+#    #+#              #
#    Updated: 2022/10/10 13:30:44 by ldutriez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=		liblcppgl

CC 		=		c++

SRC_DIR = 		$(shell find srcs -type d)
INC_DIR = 		$(shell find includes -type d) \
				$(shell find srcs -type d)

OBJ_DIR = 		objs

vpath %.cpp $(foreach dir, $(SRC_DIR), $(dir):)

SRC 	=		Application.cpp \
				Context.cpp \
				\
				Printer.cpp Writer.cpp \
				\
				Rectangle.cpp Color.cpp Texture.cpp

TEST_SRC =		test.cpp \
				${SRC}

OBJ		=		$(addprefix $(OBJ_DIR)/, $(SRC:%.cpp=%.o))
TEST_OBJ = 		$(addprefix $(OBJ_DIR)/, $(TEST_SRC:%.cpp=%.o))
#Compilation flag
CFLAGS	=		-Wall -Wextra -Werror -std=c++98 -g3

DEBUG =
ifdef DEBUG
    CFLAGS += -fsanitize=address
endif

#Include flag
IFLAGS	=		$(foreach dir, $(INC_DIR), -I$(dir))

SDL = ./ressources/great.png

# Colors

_GREY=	$'\033[30m
_RED=	$'\033[31m
_GREEN=	$'\033[32m
_YELLOW=$'\033[33m
_BLUE=	$'\033[34m
_PURPLE=$'\033[35m
_CYAN=	$'\033[36m
_WHITE=	$'\033[37m

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