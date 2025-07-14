#pragma once

#include <array>
#include <memory>
#include <ostream>
#include "Map.hpp"
#include "MLX42.h"
#include "Player.hpp"
#include "Result.hpp"
#include "TextureUtils.hpp"

struct MlxTextureDeleter {
	void operator()(mlx_texture_t* texture) const
	{
		if (texture)
			mlx_delete_texture(texture);
	}
};

using UniqueTexturePtr = std::unique_ptr<mlx_texture_t, MlxTextureDeleter>;
class Game
{
	private:
		std::optional<Player>			_player;
		std::optional<Map>				_map;
		std::array<UniqueTexturePtr, 5>	_textures{};

		Result	_validate(void) const;
		Result	_loadTextures(const std::array<std::string, INVALID_TEXTURE>& texturePaths);

	public:
		Game(void) = default;
		static Result	init(Game& game, const std::string& configFilePath);

		Map&									getMap(void);
		const Map&								getMap(void) const;
		std::array<UniqueTexturePtr, 5>&		getTextures(void);
		const std::array<UniqueTexturePtr, 5>&	getTextures(void) const;

};
std::ostream&	operator<<(std::ostream& os, const Game& config);
