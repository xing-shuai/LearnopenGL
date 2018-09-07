#pragma once
#include <map>
#include <string>
#include "GLTexture.h"
#include "ImageLoader.h"

class TextureCache {
public:
	TextureCache();
	virtual ~TextureCache();

	GLTexture getTexture(std::string textureName);

private:
	std::map<std::string, GLTexture> _textureMap;
};
