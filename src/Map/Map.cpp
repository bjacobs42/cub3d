#include "Map.hpp"
#include "Vectors.hpp"
#include <cstring>
#include <queue>
#include <set>

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
	if (!_validateFloodFillBFS(_map, _spawnLocation))
		throw std::runtime_error("Invalid map: Map is not inclosed");
}

bool	Map::_validateFloodFillBFS(const std::vector<std::string>& map, Vec2<int> start)
{
	std::queue<Vec2<int>>			toVisit;
	std::set<Vec2<int>>				visited;
	const std::vector<Vec2<int>>	directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

	auto	inBounds = [&map](const Vec2<int>& next)
	{
		return (
			next.x() >= 0 && next.x() < int(map[next.y()].size()) &&
			next.y() >= 0 && next.y() < int(map.size())
		);
	};

	auto	isWalkable = [&map](const Vec2<int>& next)
	{
		return (std::strchr(WALKABLE_TILES, map[next.y()][next.x()]));
	};

	toVisit.push(start);
	visited.insert(start);

	while (!toVisit.empty())
	{
		Vec2<int> current = toVisit.front();
		toVisit.pop();
		for (const Vec2<int>& dir : directions)
		{
			Vec2<int> next = current + dir;
			
			if (!inBounds(next))
				return false;

			if (!isWalkable(next))
				continue;

			toVisit.push(next);
			visited.insert(next);
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
