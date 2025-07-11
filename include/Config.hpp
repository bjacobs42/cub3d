#pragma once

#include <array>
#include <memory>
#include <ostream>
#include <vector>
#include "RGBA.hpp"
#include "MLX42.h"

struct MlxTextureDeleter {
	void operator()(mlx_texture_t* texture) const
	{
		if (texture)
			mlx_delete_texture(texture);
	}
};

using UniqueTexturePtr = std::unique_ptr<mlx_texture_t, MlxTextureDeleter>;
struct Config
{
	RGBA							floor;
	RGBA							ceiling;
	std::vector<std::string>		mapData;
	std::array<UniqueTexturePtr, 5>	textures{};
};
std::ostream&	operator<<(std::ostream& os, const Config& config);
