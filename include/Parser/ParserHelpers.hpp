#pragma once

#include <string>

#define WHITESPACE " \t\r\n"

namespace ParserHelpers {
	bool	endsWith(const std::string& string, const std::string& end);
	void	eraseWhiteSpace(std::string& string);
	bool	isLineEmpty(const std::string& line);
	void	rtrim(std::string& string);
}
