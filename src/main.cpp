#include <iostream>
#include "Game/Game.hpp"

int	main(int argc, char  **argv)
{
	if  (argc != 2)
	{
		std::cout << "Cub3d: Usage: ./cub3d [filename].cub" << std::endl;
		return (1);
	}

	Game	game;
	Result	result = Game::init(game, argv[1]);
	if (!result.ok)
	{
		std::cout << "Cub3d: " << result.message << std::endl;
		return (1);
	}
	std::cout << game << std::endl;
	// start render
	return (0);
}
