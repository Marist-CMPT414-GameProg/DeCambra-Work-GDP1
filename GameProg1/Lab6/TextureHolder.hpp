#ifndef HPP_TEXTUREHOLDER
#define HPP_TEXTUREHOLDER

#include <SFML/Graphics.hpp>
#include <map>

/// <summary>
/// Relies on a variant of the Singleton pattern to global access
/// to a centralized collection of texture images.
/// </summary>
class TextureHolder
{
public:
    /// <summary>
    /// Lookup a texture image asset by filename.
    /// </summary>
    /// <param name="filename">name of the image file containing the texture</param>
    /// <returns>a texture image</returns>
    static sf::Texture& GetTexture(std::string const&);

private:
    // Private/deleted constructors and assigment to enforce uniqueness
    TextureHolder();
    TextureHolder(TextureHolder const&) = delete;
    TextureHolder& operator=(TextureHolder const&) = delete;

    std::map<std::string, sf::Texture> m_Textures;

    static TextureHolder* m_s_Instance;
};

#endif HPP_TEXTUREHOLDER
