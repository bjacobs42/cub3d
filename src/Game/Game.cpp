#include "Game/Game.hpp"
#include "Game/Map.hpp"
#include "MLX42.h"
#include "Parser/Parser.hpp"
#include "Utils/Result.hpp"
#include "Utils/TextureUtils.hpp"
#include <array>
#include <exception>
#include <iostream>
#include <ostream>

Result	Game::init(Game& game, const std::string& configFilePath)
{
	Parser	parser(configFilePath);
	Result	result = parser.parse();
	if (!result.ok)
		return (result);
	Config&	config = parser.getConfig();

	try {
		game._map = Map(std::move(config.mapData));
	} catch (const std::exception& e) {
		return (Result(ERROR, e.what()));
	}
	result = game._loadTextures(config.texturePaths);
	if (!result.ok)
		return (result);
	game._map->setCeilingColor(config.ceilingColor);
	game._map->setFloorColor(config.floorColor);

	Vec2<int> spawnTile = game._map->getSpawnLocation();
	game._player = Player(Map::tileToWorldPos(spawnTile) + TILE_SIZE * 0.5, game.getMap()[spawnTile]);
	return (Result(OK));
}

Result	Game::_loadTextures(const std::array<std::string, INVALID_TEXTURE>& texturePaths)
{
	for (int i = 0; i < DOOR; ++i)
	{
		_textures[i] = UniqueTexturePtr(mlx_load_png(texturePaths[i].c_str()));
		if (!_textures[i])
			return (Result(ERROR, "Failed loading texture: ", texturePaths[i]));
	}
	if (getMap().getCharsLocation("D"))
	{
		_textures[DOOR] = UniqueTexturePtr(mlx_load_png(texturePaths[DOOR].c_str()));
		if (!_textures[DOOR])
			return (Result(ERROR, "Failed loading texture: ", texturePaths[DOOR]));
	}
	return (Result(OK));
}

std::array<UniqueTexturePtr, 5>&		Game::getTextures(void)
{
	return  (_textures);
}

const std::array<UniqueTexturePtr, 5>&	Game::getTextures(void) const
{
	return (_textures);
}

const Map&	Game::getMap(void) const
{
	return (*_map);
}

Map&	Game::getMap(void)
{
	return (*_map);
}

std::ostream&	operator<<(std::ostream& os, const Game& game)
{
	const Map&	map = game.getMap();
	os << "Floor color: " << map.getFloorColor()
	   << "\nCeiling color: " << map.getCeilingColor() << "\n";
	
	const std::array<UniqueTexturePtr, 5>&	textures = game.getTextures();
	for (int i = 0; i < 5; ++i)
	{
		mlx_texture_t	*tex = textures[i].get();

		os <<  "Texture" << i + 1 << " pixels: "; 
		if (tex)
			os << tex->height * tex->width;
		else
			os << 0;
		os << "\n";
	}
	os << "Map Data V\n" << map << std::endl;
	return (os);
}
