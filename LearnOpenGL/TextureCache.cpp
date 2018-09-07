#include "TextureCache.h"

TextureCache::TextureCache() {
	//ctor
}

TextureCache::~TextureCache() {
	//dtor
}

GLTexture TextureCache::getTexture(std::string textureName) {
	auto mit = _textureMap.find(textureName);
	if (mit == _textureMap.end()) {
		GLTexture newTexture = ImageLoader::loadPNG(textureName);

		std::pair<std::string, GLTexture> newPair(textureName, newTexture);

		_textureMap.insert(newPair);

		return newTexture;
	}
	return mit->second;
}
