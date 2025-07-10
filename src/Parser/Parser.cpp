#include "../../includes/Parser.hpp"
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

Parser::Parser(const std::string& filePath)
	: _filePath(filePath) {}

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

ParseResult	Parser::_processMap(const std::ifstream& file, const std::string& line)
{
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
			rgb[count++] = std::stoi(token);
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
	_textures[type] = mlx_load_png(path.c_str());
	if (!_textures[type])
		return (ParseResult(ERROR, "Failed to load texture " + path));
	return (ParseResult(OK));
}

ParseResult	Parser::_processLine(const std::ifstream& file, const std::string& line)
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
	else if (!_isMapProcessed())
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
		if (line.empty() || line.find_first_not_of(" \t") == std::string::npos)
			continue;
		ParseResult processResult = _processLine(file, line);
		if (!processResult.ok) return (processResult);
	}
	return (ParseResult(OK));
}
