# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/12 20:05:44 by ldutriez          #+#    #+#              #
#    Updated: 2021/11/25 21:30:09 by ldutriez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=		lcppgl

CC 		=		clang++

SRC_DIR = 		$(shell find srcs -type d)
INC_DIR = 		$(shell find includes -type d) \
				$(shell find srcs -type d)

OBJ_DIR = 		objs

vpath %.cpp $(foreach dir, $(SRC_DIR), $(dir):)

SRC 	=		test.cpp \
				\
				Application.cpp \
				Context.cpp \
				\
				Render.cpp \
				\
				Rectangle.cpp Color.cpp

OBJ		=		$(addprefix $(OBJ_DIR)/, $(SRC:%.cpp=%.o))

#Compilation flag
CFLAGS	=		-Wall -Wextra -Werror -std=c++98 -g3

DEBUG =
ifdef DEBUG
    CFLAGS += -fsanitize=address
endif

#Include flag
IFLAGS	=		$(foreach dir, $(INC_DIR), -I$(dir))

#SDL file location
SDL_FILE = /usr/include/SDL2/SDL.h

# Colors

_GREY=	$'\033[30m
_RED=	$'\033[31m
_GREEN=	$'\033[32m
_YELLOW=$'\033[33m
_BLUE=	$'\033[34m
_PURPLE=$'\033[35m
_CYAN=	$'\033[36m
_WHITE=	$'\033[37m

all:			$(SDL_FILE) $(NAME).a

$(NAME).a:		$(OBJ) Makefile
				@echo "-----\nCompiling $(_YELLOW)$@$(_WHITE) ... \c"
				@ar rc $@ $(OBJ)
				@ranlib $@
				@echo "$(_GREEN)DONE$(_WHITE)\n-----"
				
$(SDL_FILE):
				@echo -n "-----\nInstalling $(_YELLOW)sdl2$(_WHITE) ... "
				@sudo echo "installing SDL"
				@yes | sudo apt install libsdl2-2.0-0 libsdl2-gfx-1.0-0 libsdl2-net-2.0-0 libsdl2-ttf-dev
				@echo "$(_GREEN)DONE$(_WHITE)\n-----"
				
test:			$(NAME).a
				@echo "-----\nTesting $(_YELLOW)$(NAME)$(_WHITE) ... \c"
				@$(CC) $(CFLAGS) $(IFLAGS) $(OBJ) `sdl2-config --libs` -lSDL2_ttf -lSDL2_image $< -o $(NAME)
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