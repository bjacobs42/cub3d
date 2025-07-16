#pragma once

#include "Utils/RGBA.hpp"
#include "Utils/Result.hpp"
#include "Utils/TextureUtils.hpp"
#include <array>
#include <string>
#include <vector>

#define OK true
#define ERROR false

struct Config
{
	std::vector<std::string>					mapData;
	std::array<std::string, INVALID_TEXTURE>	texturePaths;
	RGBA										floorColor;
	RGBA										ceilingColor;
};

class Parser
{
	private:
		std::string					_filePath;
		Config						_config;

		Result	_processMap(std::ifstream& file, std::string& line);
		Result	_processLine(std::ifstream& file, std::string& line);
		Result	_processFnC(const std::string& key, const std::string& color);
		Result	_processTexture(const std::string& key,  const std::string& path);

	public:
		explicit Parser(const std::string& filePath);
		~Parser(void);

		Result		parse(void);

		Config&		getConfig(void);
};
