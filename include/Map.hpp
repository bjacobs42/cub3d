#pragma once

#include "Vec2.hpp"
#include <optional>
#include <string>
#include <vector>
class Map
{
	private:
		Vec2<int>					_dimension;
		std::vector<std::string>	_map;

		void	_initDimensions(void);

	public:
		explicit Map(std::vector<std::string>&& mapData);
		explicit Map(const std::vector<std::string>& mapData);
		~Map(void);

		const std::vector<std::string>&	getMap(void) const;
		std::optional<Vec2<double>>		getPlayerStartPosition(void) const;

};

std::ostream&	operator<<(std::ostream &os, const Map& map);
