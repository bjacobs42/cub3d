#pragma once

#include <array>
#include <string>
#include "RGBA.hpp"
#include "../MLX42/include/MLX42/MLX42.h"

#define OK true
#define ERROR false

enum TextureType {
	NO,
	SO,
	WE,
	EA,
	DOOR,
	INVALID_TEXTURE
};

struct config
{
	RGBA							floor;
	RGBA							ceiling;
	std::array<mlx_texture_t*, 5>	textures{};
	std::array<xpm_t*, 5>			xpms{};
};

struct ParseResult {
	bool		ok;
	std::string	message;

	ParseResult(bool ok, const std::string& msg = "")
		: ok(ok), message(msg) {}
};

class Parser
{
	private:
		std::string						_filePath;
		std::array<mlx_texture_t*, 5>	_textures{};
		config							_configData;

		ParseResult	_processMap(const std::ifstream& file, const std::string& line);
		ParseResult	_processLine(const std::ifstream& file, const std::string& line);
		ParseResult	_processFnC(const std::string& key, const std::string& color);
		ParseResult	_processTexture(const std::string& key,  const std::string& path);

		bool		_endsWith(const std::string& string, const std::string& end);
		void		_eraseWhiteSpace(std::string& string);
	
	public:
		explicit Parser(const std::string& filePath);
		~Parser();

		ParseResult	parse(void);
};
