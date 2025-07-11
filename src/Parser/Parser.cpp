#include "../../include/Parser.hpp"
#include <algorithm>
#include <exception>
#include <fstream>
#include <sstream>

TextureType	keyToTextureType(const std::string& key)
{
	if (key == "NO")  return (TextureType::NO);
	if (key == "SO")  return (TextureType::SO);
	if (key == "WE")  return (TextureType::WE);
	if (key == "EA")  return (TextureType::EA);
	return (TextureType::INVALID_TEXTURE);
}

bool	Parser::_checkMapLine(const std::string& line)
{
	return (line.find_first_not_of(MAP_CHARS) == std::string::npos);
}

ParseResult	Parser::_checkData(void)
{
	if (!_isMapProcessed)
		return (ParseResult(ERROR, "No map found"));
	for (const UniqueTexturePtr& texture : _configData.textures)
	{
		if (!texture)
			return (ParseResult(ERROR, "Missing textures or no textures found"));
	}
	return (ParseResult(OK));
}

Parser::Parser(const std::string& filePath)
	: _filePath(filePath) {}

Parser::~Parser(void)
{}

bool	Parser::_isLineEmpty(const std::string& line)
{
	return (line.find_first_not_of(WHITESPACE) == std::string::npos);
}

void	Parser::_eraseWhiteSpace(std::string& string)
{
	string.erase(
		std::remove_if(string.begin(), string.end(), [](unsigned char ch) {
			return (std::isspace(ch));
		})
	);
}

bool	Parser::_endsWith(const std::string& string, const std::string& end)
{
	if (string.size() < end.size()
		|| string.compare(string.size() - end.size(), end.size(), end))
	{
		return (false);
	}
	return (true);
}

void	Parser::_rtrim(std::string& string)
{
	size_t	end = string.find_last_not_of(WHITESPACE);
	if (end != std::string::npos)
		string.erase(end + 1);
	else
		string.clear();
}

ParseResult	Parser::_processMap(std::ifstream& file, std::string& line)
{
	do 
	{
		_rtrim(line);
		if (line.empty())
			break;
		if (!_checkMapLine(line))
			return (ParseResult(ERROR, "Invalid map format: " + line));
		_configData.mapData.push_back(line);
	}
	while (std::getline(file, line));
	if (_configData.mapData.empty())
		return (ParseResult(ERROR, "Missing map section"));
	_isMapProcessed = true;
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
			return (ParseResult(ERROR, "Invalid rgb format: " + color));
		try
		{
			rgb[count] = std::stoi(token);
			if (rgb[count] < 0) throw std::exception();
			count++;
		}
		catch (const std::exception& e)
		{
			return (ParseResult(ERROR, "Invalid color value: " + color));
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
		return (ParseResult(ERROR, "Missing texture for " + key));
	if (!_endsWith(path, ".png"))
		return (ParseResult(ERROR, "Unsupported texture extension"));

	TextureType	type = keyToTextureType(key);
	_configData.textures[type] = UniqueTexturePtr(mlx_load_png(path.c_str()));
	if (!_configData.textures[type])
		return (ParseResult(ERROR, "Failed to load texture " + path));
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
		_eraseWhiteSpace(color);
		return (_processFnC(key, color));
	}
	else if (key == "NO" || key == "SO" || key == "WE" ||  key == "EA" || key == "DOOR")
	{
		std::string	texturePath;
		std::getline(iss, texturePath);

		_eraseWhiteSpace(texturePath);
		return (_processTexture(key, texturePath));
	}
	else if (!_isMapProcessed)
		return (_processMap(file, line));
	else
		return (ParseResult(ERROR, "Unexpected line or misplaced content: " + line));
}

ParseResult	Parser::parse(void)
{
	std::ifstream	file;
	std::string		line;

	if (!_endsWith(_filePath, ".cub"))
		return (ParseResult(ERROR, "Unsupported file extension"));
	file.open(_filePath);
	if (!file.is_open())
		return (ParseResult(ERROR, "Invalid file"));

	while (std::getline(file, line))
	{
		if (_isLineEmpty(line))
			continue;
		ParseResult processResult = _processLine(file, line);
		if (!processResult.ok) return (processResult);
	}
	return (_checkData());
}
