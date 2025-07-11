#pragma once

#include <array>
#include <memory>
#include <ostream>
#include <string>
#include <vector>
#include "RGBA.hpp"
#include "../MLX42/include/MLX42/MLX42.h"

#define OK true
#define ERROR false
#define WHITESPACE " \t\r\n"
#define MAP_CHARS "10DNEWS \t"

enum TextureType {
	NO,
	SO,
	WE,
	EA,
	DOOR,
	INVALID_TEXTURE
};

struct MlxTextureDeleter {
	void operator()(mlx_texture_t* texture) const
	{
		if (texture)
			mlx_delete_texture(texture);
	}
};

using UniqueTexturePtr = std::unique_ptr<mlx_texture_t, MlxTextureDeleter>;
struct Config
{
	RGBA							floor;
	RGBA							ceiling;
	std::vector<std::string>		mapData;
	std::array<UniqueTexturePtr, 5>	textures{};
};
std::ostream&	operator<<(std::ostream& os, const Config& config);

struct ParseResult {
	bool		ok;
	std::string	message;

	ParseResult(bool ok, const std::string& msg = "")
		: ok(ok), message(msg) {}
};

class Parser
{
	private:
		bool		_isMapProcessed;
		std::string	_filePath;
		Config		_configData;

		ParseResult	_processMap(std::ifstream& file, std::string& line);
		ParseResult	_processLine(std::ifstream& file, std::string& line);
		ParseResult	_processFnC(const std::string& key, const std::string& color);
		ParseResult	_processTexture(const std::string& key,  const std::string& path);

		bool		_endsWith(const std::string& string, const std::string& end);
		void		_eraseWhiteSpace(std::string& string);
		bool		_isLineEmpty(const std::string& line);
		void		_rtrim(std::string& string);

		bool		_checkMapLine(const std::string& line);
		ParseResult	_checkData(void);

	public:
		explicit Parser(const std::string& filePath);
		~Parser(void);

		ParseResult		parse(void);
		const Config&	getConfig(void) const;
};
