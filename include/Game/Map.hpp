#pragma once

#include "Utils/RGBA.hpp"
#include "Utils/Result.hpp"
#include "Utils/Vectors.hpp"
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

#define WALKABLE_TILES "0D"
#define	PLAYER_CHARS "NEWS"
#define MAP_CHARS "10D \t"

#define TILE_SIZE 8

class MapError : public std::runtime_error
{
	public:
		MapError(const std::string& msg, const::std::string& line, const Vec2<int>& loc, char lineWrap = '"')
			: std::runtime_error(Result::formatError(msg, line, loc, lineWrap)) {}

};

class Map
{
	private:
		RGBA						_floorColor;
		RGBA						_ceilingColor;
		Vec2<int>					_dimension;
		Vec2<int>					_spawnLocation;
		std::vector<std::string>	_map;

		void		_init(void);
		static bool	_validateFloodFillBFS(const Map& map, Vec2<int> start);

	public:
		explicit Map(std::vector<std::string>&& mapData);
		explicit Map(const std::vector<std::string>& mapData);
		~Map(void);

		static Vec2<double>	tileToWorldPos(const Vec2<int>& tile);
		static Vec2<double>	WorldPosToTile(const Vec2<double>& worldPos);

		const std::vector<std::string>&	getRawMap(void) const;
		std::optional<Vec2<double>>		getCharsLocation(const std::string& chars) const;
		Vec2<int>						getSpawnLocation(void) const;
		RGBA							getFloorColor(void) const;
		RGBA							getCeilingColor(void) const;

		void	setFloorColor(const RGBA& color);
		void	setCeilingColor(const RGBA& color);

		bool	isWalkable(const Vec2<int>& pos) const;
		bool	inBounds(const Vec2<int>& pos) const;

		char	operator[](const Vec2<int>& i) const;
};

std::ostream&	operator<<(std::ostream &os, const Map& map);
