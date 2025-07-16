#pragma once

#include "Vectors.hpp"
#include <optional>
#include <sstream>
#include <string>

struct Result {
	bool		ok;
	std::string	message;

	Result(
		bool ok,
		const std::string& msg = "",
		const std::optional<std::string>& line = std::nullopt,
		const std::optional<Vec2<int>>& loc = std::nullopt,
		char lineWrap = '"'
	)
		: ok(ok), message(formatError(msg, line, loc, lineWrap)) {}

	static std::string	formatError(
		const std::string& msg,
		const std::optional<std::string>& line,
		const std::optional<Vec2<int>>& loc,
		char lineWrap = '"'
	)
	{
		std::stringstream	ss;

		ss << msg;
		if (loc)
			ss << " at (" << loc->x() << "," << loc->y() << "): ";
		if (line)
			ss << lineWrap << *line << lineWrap;

		return (ss.str());
	}
};

