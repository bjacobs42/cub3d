#include "Config.hpp"
#include "MLX42.h"
#include <ostream>

std::ostream&	operator<<(std::ostream& os, const Config& config)
{
	os << "Floor color: " << config.floorColor 
	   << "\nCeiling color: " << config.ceilingColor << "\n";
	for (int i = 0; i < 5; ++i)
	{
		mlx_texture_t	*tex = config.textures[i].get();

		os <<  "Texture" << i + 1 << " pixels: "; 
		if (tex)
			os << tex->height * tex->width;
		else
			os << 0;
		os << "\n";
	}
	if (config.map)
		os << "Map Data V\n" << *config.map << std::endl;
	else
		os << "No map data" << std::endl;
	return (os);
}
