#pragma once

#include <string>

enum TextureType {
	NO,
	SO,
	WE,
	EA,
	DOOR,
	INVALID_TEXTURE
};

namespace TextureUtils {
	TextureType	keyToTextureType(const std::string& key);
}

