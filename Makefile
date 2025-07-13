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
PARSER_DIR	:= Parser/
RGBA_DIR	:= RGBA/
CONFIG_DIR	:= Config/
MAP_DIR		:= Map/
UTILS_DIR	:= Utils/
INC_DIR		:= ./include/
OBJ_DIR 	:= ./obj/
SRC_DIR 	:= ./src/

HEADER_FILES 	:= Map.hpp Player.hpp RGBA.hpp Vectors.hpp TextureUtils.hpp
HEADER_FILES	+= $(addprefix $(PARSER_DIR),Parser.hpp ParserHelpers.hpp)

PARSER_FILES	:= Parser.cpp ParserHelpers.cpp
UTILS_FILES		:= TextureUtils.cpp
MAP_FILES		:= Map.cpp
RGBA_FILES		:= RGBA.cpp
CONFIG_FILES	:= Config.cpp

HEADERS := $(addprefix $(INC_DIR),$(HEADER_FILES))

SRC :=	main.cpp
SRC +=	$(addprefix $(PARSER_DIR),$(PARSER_FILES))
SRC +=	$(addprefix $(RGBA_DIR),$(RGBA_FILES))
SRC +=	$(addprefix $(CONFIG_DIR),$(CONFIG_FILES))
SRC +=	$(addprefix $(MAP_DIR),$(MAP_FILES))
SRC +=	$(addprefix $(UTILS_DIR),$(UTILS_FILES))

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
