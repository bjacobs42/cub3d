#pragma once

#include "Config.hpp"
#include <cstdint>
#include <string>

#define OK true
#define ERROR false
#define	PLAYER_CHARS "NEWS"
#define MAP_CHARS "10D \t"

enum Flags : uint8_t {
	DOOR_INCLUDED = 1 << 0,
	PLAYER_FOUND = 1 << 1
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
		uint8_t		_flags;
		std::string	_filePath;
		Config		_configData;

		ParseResult	_processMap(std::ifstream& file, std::string& line);
		ParseResult	_processLine(std::ifstream& file, std::string& line);
		ParseResult	_processFnC(const std::string& key, const std::string& color);
		ParseResult	_processTexture(const std::string& key,  const std::string& path);

		ParseResult	_checkMapLine(const std::string& line);
		ParseResult	_checkData(void);

	public:
		explicit Parser(const std::string& filePath);
		~Parser(void);

		ParseResult		parse(void);
		const Config&	getConfig(void) const;
};
