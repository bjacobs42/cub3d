#pragma once

#include <array>
#include <memory>
#include <optional>
#include <ostream>
#include "Map.hpp"
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
	RGBA							floorColor;
	RGBA							ceilingColor;
	std::optional<Map>				map;
	std::array<UniqueTexturePtr, 5>	textures{};
};
std::ostream&	operator<<(std::ostream& os, const Config& config);
