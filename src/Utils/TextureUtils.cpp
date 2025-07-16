#include "Utils/TextureUtils.hpp"

namespace TextureUtils {
	TextureType	keyToTextureType(const std::string& key)
	{
		if (key == "NO")  return (TextureType::NO);
		if (key == "SO")  return (TextureType::SO);
		if (key == "WE")  return (TextureType::WE);
		if (key == "EA")  return (TextureType::EA);
		if (key == "DOOR")  return (TextureType::DOOR);
		return (TextureType::INVALID_TEXTURE);
	}
}
