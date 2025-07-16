#include "Parser/Parser.hpp"
#include "Parser/ParserHelpers.hpp"
#include "Utils/Result.hpp"
#include "Utils/TextureUtils.hpp"
#include <fstream>
#include <sstream>
#include <string>

Parser::Parser(const std::string& filePath)
	: _filePath(filePath) {}

Parser::~Parser(void)
{}

Result	Parser::_processMap(std::ifstream& file, std::string& line)
{
	do 
	{
		ParserHelpers::rtrim(line);
		if (line.empty())
			break;
		_config.mapData.push_back(line);
	}
	while (std::getline(file, line));
	if (_config.mapData.empty())
		return (Result(ERROR, "Missing data: No map found"));
	return (Result(OK));
}

Result	Parser::_processFnC(const std::string& key, const std::string& color)
{
	std::string	token;
	int			rgb[3];
	int			count;

	if (color.empty())
		return (Result(ERROR, "Missing color: No rgb value found after ", key));

	count = 0;
	std::stringstream ss(color);
	while (std::getline(ss, token, ','))
	{
		if (count >= 3)
			return (Result(ERROR, "Invalid rgb format: ", color));
		try
		{
			rgb[count] = std::stoi(token);
			if (rgb[count] < 0) throw std::exception();
			count++;
		}
		catch (const std::exception& e)
		{
			return (Result(ERROR, "Invalid rgb value: ", color));
		}
	}
	if (key == "F") 
		_config.floorColor = RGBA(rgb[0], rgb[1], rgb[2]);
	else
		_config.ceilingColor = RGBA(rgb[0], rgb[1], rgb[2]);
	return (Result(OK));
}

Result	Parser::_processTexture(const std::string& key,  const std::string& path)
{
	if (path.empty())
		return (Result(ERROR, "Missing texture: No texture found for ", key));
	if (!ParserHelpers::endsWith(path, ".png"))
		return (Result(ERROR, "Invalid texture: Unsupported texture file"));

	TextureType	type = TextureUtils::keyToTextureType(key);
	if (type == TextureType::INVALID_TEXTURE)
		return (Result(ERROR, "Unknown texture type: ", key));
	_config.texturePaths[type] = path;
	return (Result(OK));
}

Result	Parser::_processLine(std::ifstream& file, std::string& line)
{
	std::istringstream	iss(line);
	std::string			key;

	iss >> key;
	if (key == "F" || key == "C")
	{
		std::string	color;
		std::getline(iss, color);
		ParserHelpers::eraseWhiteSpace(color);
		return (_processFnC(key, color));
	}
	else if (key == "NO" || key == "SO" || key == "WE" ||  key == "EA" || key == "DOOR")
	{
		std::string	texturePath;
		std::getline(iss, texturePath);

		ParserHelpers::eraseWhiteSpace(texturePath);
		return (_processTexture(key, texturePath));
	}
	else if (_config.mapData.empty())
		return (_processMap(file, line));
	else
		return (Result(ERROR, "Unexpected line or misplaced content: ", line));
}

Config&		Parser::getConfig(void)
{
	return (_config);
}

Result	Parser::parse(void)
{
	std::ifstream	file;
	std::string		line;

	if (!ParserHelpers::endsWith(_filePath, ".cub"))
		return (Result(ERROR, "Unsupported file"));
	file.open(_filePath);
	if (!file.is_open())
		return (Result(ERROR, "Invalid cub file"));

	while (std::getline(file, line))
	{
		if (ParserHelpers::isLineEmpty(line))
			continue;
		Result processResult = _processLine(file, line);
		if (!processResult.ok) return (processResult);
	}
	return (Result(OK));
}
