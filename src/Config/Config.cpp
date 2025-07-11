#include "Config.hpp"
#include "MLX42.h"
#include <ostream>

std::ostream&	operator<<(std::ostream& os, const Config& config)
{
	os << "Floor color: " << config.floor << "\nCeiling color: " << config.ceiling << "\n";
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
	os << "Map Data V\n";
	for (const std::string& mapLine : config.mapData)
		os << mapLine << "\n";
	os << std::endl;
	return (os);
}
