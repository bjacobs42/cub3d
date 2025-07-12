#include "Map.hpp"
#include "Parser/Parser.hpp"
#include <algorithm>
#include <optional>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

Map::Map(std::vector<std::string>&& mapData)
	: _map(std::move(mapData))
{
	_initDimensions();
}

Map::Map(const std::vector<std::string>& mapData)
	: _map(mapData)
{
	_initDimensions();
}

Map::~Map(void) {}

void	Map::_initDimensions(void)
{
	_dimension.y = int(_map.size());
	for (const std::string& mapLine : _map)
		_dimension.x = std::max(int(mapLine.size()), _dimension.x);
}

std::optional<Vec2<double>>	Map::getPlayerStartPosition(void) const
{
	for (int y = 0; y < _dimension.y; ++y)
	{
		size_t found = _map[y].find_first_of(PLAYER_CHARS);
		if (found != std::string::npos)
			return (Vec2(double(found), double(y)));
	}
	return (std::nullopt);
}

const std::vector<std::string>&	Map::getMap(void) const
{
	return (_map);
}

std::ostream&	operator<<(std::ostream &os, const Map& map)
{
	for (const std::string& mapLine : map.getMap())
		os << mapLine << "\n";
	return (os);
}
