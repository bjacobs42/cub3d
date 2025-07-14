#include "Map.hpp"
#include "RGBA.hpp"
#include "Vectors.hpp"
#include <cassert>
#include <cstring>
#include <iostream>
#include <queue>
#include <unordered_set>

Map::Map(std::vector<std::string>&& mapData)
	: _map(std::move(mapData))
{
	_init();
}

Map::Map(const std::vector<std::string>& mapData)
	: _map(mapData)
{
	_init();
}

Map::~Map(void) {}

void	Map::_init(void)
{
	bool	spawnFound = false;
	int		mapHeight = int(_map.size());

	_dimension.y() = mapHeight;
	for (int y = 0; y < mapHeight; ++y)
	{
		const std::string& row = _map[y];
		int	rowWidth = row.size();
		_dimension.x() = std::max(rowWidth, _dimension.x());

		for (int x = 0; x < rowWidth; ++x)
		{
			char	tile = row[x];

			if (std::strchr(PLAYER_CHARS, tile))
			{
				if (spawnFound)
					throw MapError("Invalid map: Second player spawn location", row, {x, y});
				_spawnLocation = {x, y};
				spawnFound = true;
			}
			else if (!std::strchr(MAP_CHARS, tile))
				throw MapError("Invalid map: Bad map format", row, {x, y});
		}
	}
	if (!spawnFound)
		throw std::runtime_error("Invalid map: No player spawn location");
	if (!_validateFloodFillBFS(*this, _spawnLocation))
		throw std::runtime_error("Invalid map: Map is not inclosed");
}

bool	Map::_validateFloodFillBFS(const Map& map, Vec2<int> start)
{
	std::queue<Vec2<int>>					toVisit;
	std::unordered_set<Vector<int, 2>>		visited;
	const std::vector<Vec2<int>>			directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

	toVisit.push(start);
	visited.insert(start);

	while (!toVisit.empty())
	{
		Vec2<int> current = toVisit.front();
		toVisit.pop();

		for (const Vec2<int>& dir : directions)
		{
			Vec2<int> next = current + dir;
			
			if (!map.inBounds(next))
				return false;

			if (!map.isWalkable(next) || visited.count(next))
				continue;

			visited.insert(next);
			toVisit.push(next);
		}
	}
	return (true);
}

std::optional<Vec2<double>>	Map::getCharsLocation(const std::string& needles) const
{
	int	mapHeight = _dimension.y();

	for (int y = 0; y < mapHeight; ++y)
	{
		size_t x = _map[y].find_first_of(needles);
		if (x != std::string::npos)
			return (Vec2(double(x), double(y)));
	}
	return (std::nullopt);
}

void	Map::setFloorColor(const RGBA& newColor)
{
	_floorColor = newColor;
}

void	Map::setCeilingColor(const RGBA& newColor)
{
	_ceilingColor = newColor;
}

RGBA	Map::getFloorColor(void) const
{
	return (_floorColor);
}

RGBA	Map::getCeilingColor(void) const
{
	return (_ceilingColor);
}

const std::vector<std::string>&	Map::getRawMap(void) const
{
	return (_map);
}

bool	Map::inBounds(const Vec2<int>& pos) const
{
	return (
		pos.y() >= 0 && pos.y() < int(_map.size()) &&
		pos.x() >= 0 && pos.x() < int(_map[pos.y()].size())
	);
}

bool	Map::isWalkable(const Vec2<int>& pos) const
{
	return (std::strchr(WALKABLE_TILES, _map[pos.y()][pos.x()]));
};

char	Map::operator[](const Vec2<int>& i) const
{
	if (!inBounds(i))
		throw std::out_of_range("Index out of map bounds");
	return (_map[i.y()][i.x()]);
}

std::ostream&	operator<<(std::ostream &os, const Map& map)
{
	for (const std::string& mapLine : map.getRawMap())
		os << mapLine << "\n";
	return (os);
}

