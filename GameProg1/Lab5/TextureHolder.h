#ifndef TEXTURE_HOLDER_H
#define TEXTURE_HOLDER_H

#include <SFML/Graphics.hpp>
#include <map>

class TextureHolder
{
public:
	static sf::Texture& GetTexture(std::string const& filename);

private:
	// Private/deleted constructors and assignment to enforce uniqueness
	TextureHolder();
	TextureHolder(TextureHolder const&) = delete;
	TextureHolder& operator = (TextureHolder const&) = delete;

	std::map<std::string, sf::Texture> m_Textures;

	static TextureHolder* m_s_Instance;
};
#endif TEXTURE_HOLDER_H
