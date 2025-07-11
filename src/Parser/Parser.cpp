#include "Parser/Parser.hpp"
#include "Parser/ParserHelpers.hpp"
#include "TextureUtils.hpp"
#include <cstring>
#include <exception>
#include <fstream>
#include <sstream>

bool	Parser::_checkMapLine(const std::string& line)
{
	for (char c : line)
	{
		if (c == 'D' && !(_flags & DOOR_INCLUDED))
			_flags |= DOOR_INCLUDED;
		if (!std::strchr(MAP_CHARS, c))
			return (false);
	}
	return (true);
}

ParseResult	Parser::_checkData(void)
{
	if (!(_flags & MAP_PROCESSED))
		return (ParseResult(ERROR, "No map found"));
	for (size_t i = 0; i < TextureType::DOOR; ++i)
	{
		if (!_configData.textures[i].get())
			return (ParseResult(ERROR, "Missing textures or no textures found"));
	}
	if (_flags & DOOR_INCLUDED && !_configData.textures[TextureType::DOOR])
		return (ParseResult(ERROR, "Missing texture or no texture found for door"));
	return (ParseResult(OK));
}

Parser::Parser(const std::string& filePath)
	: _filePath(filePath) {}

Parser::~Parser(void)
{}

ParseResult	Parser::_processMap(std::ifstream& file, std::string& line)
{
	do 
	{
		ParserHelpers::rtrim(line);
		if (line.empty())
			break;
		if (!_checkMapLine(line))
			return (ParseResult(ERROR, "Invalid map format: \"" + line + "\""));
		_configData.mapData.push_back(line);
	}
	while (std::getline(file, line));
	if (_configData.mapData.empty())
		return (ParseResult(ERROR, "Missing map section"));
	_flags |= MAP_PROCESSED;
	return (ParseResult(OK));
}

ParseResult	Parser::_processFnC(const std::string& key, const std::string& color)
{
	std::string	token;
	int			rgb[3];
	int			count;

	if (color.empty())
		return (ParseResult(ERROR, "Missing color for " + key));

	count = 0;
	std::stringstream ss(color);
	while (std::getline(ss, token, ','))
	{
		if (count >= 3)
			return (ParseResult(ERROR, "Invalid rgb format: \"" + color + "\""));
		try
		{
			rgb[count] = std::stoi(token);
			if (rgb[count] < 0) throw std::exception();
			count++;
		}
		catch (const std::exception& e)
		{
			return (ParseResult(ERROR, "Invalid color value: \"" + color + "\""));
		}
	}
	if (key == "F") 
		_configData.floor = RGBA(rgb[0], rgb[1], rgb[2]);
	else
		_configData.ceiling = RGBA(rgb[0], rgb[1], rgb[2]);
	return (ParseResult(OK));
}

ParseResult	Parser::_processTexture(const std::string& key,  const std::string& path)
{
	if (path.empty())
		return (ParseResult(ERROR, "Missing texture for \"" + key + "\""));
	if (!ParserHelpers::endsWith(path, ".png"))
		return (ParseResult(ERROR, "Unsupported texture extension"));

	TextureType	type = TextureUtils::keyToTextureType(key);
	if (type == TextureType::INVALID_TEXTURE)
		return (ParseResult(ERROR, "Unknown texture type \"" + key + "\""));
	_configData.textures[type] = UniqueTexturePtr(mlx_load_png(path.c_str()));
	if (!_configData.textures[type])
		return (ParseResult(ERROR, "Failed to load texture \"" + path + "\""));
	return (ParseResult(OK));
}

ParseResult	Parser::_processLine(std::ifstream& file, std::string& line)
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
	else if (!(_flags & MAP_PROCESSED))
		return (_processMap(file, line));
	else
		return (ParseResult(ERROR, "Unexpected line or misplaced content: " + line));
}

const Config&	Parser::getConfig(void) const
{
	return (_configData);
}

ParseResult	Parser::parse(void)
{
	std::ifstream	file;
	std::string		line;

	if (!ParserHelpers::endsWith(_filePath, ".cub"))
		return (ParseResult(ERROR, "Unsupported file extension"));
	file.open(_filePath);
	if (!file.is_open())
		return (ParseResult(ERROR, "Invalid cub file"));

	while (std::getline(file, line))
	{
		if (ParserHelpers::isLineEmpty(line))
			continue;
		ParseResult processResult = _processLine(file, line);
		if (!processResult.ok) return (processResult);
	}
	return (_checkData());
}
