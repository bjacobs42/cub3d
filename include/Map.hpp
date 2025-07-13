#pragma once

#include "Vectors.hpp"
#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#define WALKABLE_TILES "0D"
#define	PLAYER_CHARS "NEWS"
#define MAP_CHARS "10D \t"

class MapError : public std::runtime_error
{
	public:
		MapError(const std::string& msg, const::std::string& line, const Vec2<int>& loc, char lineWrap = '"')
			: std::runtime_error(formatError(msg, line, loc, lineWrap)) {}

		static std::string	formatError(
			const std::string& msg, const::std::string& line, const Vec2<int>& loc, char lineWrap = '"'
		)
		{
			std::stringstream	ss;

			ss << msg << " at (" << loc.x() << "," << loc.y() << "): " << lineWrap << line << lineWrap;
			return (ss.str());
		}
};

class Map
{
	private:
		Vec2<int>					_dimension;
		Vec2<int>					_spawnLocation;
		std::vector<std::string>	_map;

		void	_init(void);
		bool	_validateFloodFillBFS(const std::vector<std::string>& map, Vec2<int> start);

	public:
		explicit Map(std::vector<std::string>&& mapData);
		explicit Map(const std::vector<std::string>& mapData);
		~Map(void);

		const std::vector<std::string>&	getMap(void) const;
		std::optional<Vec2<double>>		getCharsLocation(const std::string& chars) const;
		Vec2<double>					getSpawnLocation(void) const;
};

std::ostream&	operator<<(std::ostream &os, const Map& map);
