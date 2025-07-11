#include <iostream>
#include "Parser/Parser.hpp"

int	main(int argc, char  **argv)
{
	if  (argc != 2)
	{
		std::cout << "Cub3d: Usage: ./cub3d [filename].cub" << std::endl;
		return (1);
	}
	Parser parser(argv[1]);
	ParseResult result = parser.parse();
	if (!result.ok)
	{
		std::cout << "Cub3d: " << result.message << std::endl;
		return (1);
	}
	const Config& config = parser.getConfig();
	std::cout << config << std::endl;
	return (0);
}
