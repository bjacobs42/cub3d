#include "Parser/ParserHelpers.hpp"
#include <algorithm>

namespace ParserHelpers {
	bool	isLineEmpty(const std::string& line)
	{
		return (line.find_first_not_of(WHITESPACE) == std::string::npos);
	}

	void	eraseWhiteSpace(std::string& string)
	{
		string.erase(
			std::remove_if(string.begin(), string.end(), [](unsigned char ch) {
				return (std::isspace(ch));
			}),
			string.end()
		);
	}

	bool	endsWith(const std::string& string, const std::string& end)
	{
		if (string.size() < end.size()
			|| string.compare(string.size() - end.size(), end.size(), end))
		{
			return (false);
		}
		return (true);
	}

	void	rtrim(std::string& string)
	{
		size_t	end = string.find_last_not_of(WHITESPACE);
		if (end != std::string::npos)
			string.erase(end + 1);
		else
			string.clear();
	}
}
