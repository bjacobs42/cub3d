# Makefile for cub3d

# Variables
NAME	:= cub3D
MLX_DIR	:= MLX42/
MLX42	:= $(MLX_DIR)build/
LIBSA	:= $(MLX42)libmlx42.a
INCLUDE := -I MLX42 -I include

# Compiler and Flags
CC := c++
CFLAGS := -g -Wall -Wextra -Werror -fsanitize=address

ifeq ($(shell uname), Linux)
	MLX_FLAGS := -ldl -lglfw -pthread -lm
else
	MLX_FLAGS := -lglfw -L"/opt/homebrew/Cellar/glfw/3.3.8/lib" -framework Cocoa -framework OpenGL -framework IOKit
endif

# Directories and Files
OBJ_DIR := ./obj/
SRC_DIR := ./src/
HEADERS := include/Map.hpp include/Parser.hpp include/Player.hpp include/RGBA.hpp include/Vec2.hpp

S_PARSER_DIR	:= Parser/
S_RGBA_DIR		:= RGBA/
S_CONFIG_DIR	:= Config/

S_PARSER_FILES	:= Parser.cpp
S_RGBA_FILES	:= RGBA.cpp
S_CONFIG_FILES	:= Config.cpp

SRC :=	main.cpp
SRC +=	$(addprefix $(S_PARSER_DIR),$(S_PARSER_FILES))
SRC +=	$(addprefix $(S_RGBA_DIR),$(S_RGBA_FILES))
SRC +=	$(addprefix $(S_CONFIG_DIR),$(S_CONFIG_FILES))

OBJ := $(addprefix $(OBJ_DIR),$(SRC:.cpp=.o))

# Targets
.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ) | $(MLX42)
	@echo $(Yellow) Building.. 🏠$(Color_Off)
	@make -C $(MLX42)
	@$(CC) -Ofast -o $(NAME) $^ $(LIBSA) $(CFLAGS) $(INCLUDE) $(MLX_FLAGS)
	@echo $(Green) Complete ✅ $(Color_Off)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp $(HEADERS) | $(OBJ_DIR)
	@mkdir -p $(@D)
	@echo $(Purple) Compiling.. 🧱 $< $(Color_Off)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

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
