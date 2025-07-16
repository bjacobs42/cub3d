# Makefile for cub3d

# Variables
NAME	:= cub3D
MLX_DIR	:= MLX42/
MLX42	:= $(MLX_DIR)build/
LIBSA	:= $(MLX42)libmlx42.a
INCLUDE := -I $(MLX_DIR)include/MLX42 -I include

# Compiler and Flags
CC := c++
CFLAGS := -g -Wall -Wextra -Werror -fsanitize=address

ifeq ($(shell uname), Linux)
	MLX_FLAGS := -ldl -lglfw -pthread -lm
else
	MLX_FLAGS := -lglfw -L"/opt/homebrew/Cellar/glfw/3.3.8/lib" -framework Cocoa -framework OpenGL -framework IOKit
endif

# Directories and Files
INC_DIR			:= ./include/
OBJ_DIR		 	:= ./obj/
SRC_DIR 		:= ./src/

PARSER_DIR		:= Parser/
GAME_DIR		:= Game/
UTILS_DIR		:= Utils/
PLAYER_DIR		:= $(GAME_DIR)Player/

PARSER_FILES	:= Parser.cpp ParserHelpers.cpp
UTILS_FILES		:= TextureUtils.cpp RGBA.cpp Window.cpp
GAME_FILES		:= Game.cpp Map.cpp
PLAYER_FILES	:= Player.cpp Camera.cpp

HEADER_FILES 	:= $(UTILS_DIR)Vectors.hpp $(UTILS_DIR)Result.hpp

SRC :=	$(addprefix $(PARSER_DIR),$(PARSER_FILES))
SRC +=	$(addprefix $(GAME_DIR),$(GAME_FILES))
SRC +=	$(addprefix $(UTILS_DIR),$(UTILS_FILES))
SRC +=	$(addprefix $(PLAYER_DIR),$(PLAYER_FILES))

HEADER_FILES += $(SRC:.cpp=.hpp)

SRC +=	main.cpp

HEADERS := $(addprefix $(INC_DIR),$(HEADER_FILES))
OBJ := $(addprefix $(OBJ_DIR),$(SRC:.cpp=.o))

# Targets
.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ) | $(MLX43)
	@echo $(Yellow) Building.. 🏠$(Color_Off)
	@make -C $(MLX42)
	@$(CC) -Ofast -o $(NAME) $^ $(LIBSA) $(CFLAGS) $(INCLUDE) $(MLX_FLAGS)
	@echo $(Green) Complete ✅ $(Color_Off)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp $(HEADERS) | $(OBJ_DIR)
	@mkdir -p $(@D)
	@echo $(Purple) Compiling.. 🧱 $< $(Color_Off)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(MLX42):
	@cmake $(MLX_DIR) -B $(MLX_DIR)build

$(OBJ_DIR):
	@echo "$(YELLOW)Creating folders... $(NC)🗂"
	@mkdir $@

clean:
	@echo $(Cyan) Sweeping.. 💥 $(Color_Off)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo $(Red) Thorough sweeping.. 💥 $(Color_Off)
	@$(MAKE) -C MLX42/build clean
	@rm -f $(NAME)

re: fclean all

# Color Codes
Color_Off = "\033[0m"
Yellow = "\033[0;33m"
Purple = "\033[0;35m"
Cyan = "\033[0;36m"
Green = "\033[0;32m"
Red = "\033[0;31m"
