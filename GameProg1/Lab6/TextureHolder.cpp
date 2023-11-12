#include "TextureHolder.hpp"
#include <assert.h>

using namespace sf;
using namespace std;

TextureHolder* TextureHolder::m_s_Instance = nullptr;

TextureHolder::TextureHolder()
{
    assert(m_s_Instance == nullptr); // This should never happen!
    m_s_Instance = this;
}

sf::Texture& TextureHolder::GetTexture(std::string const& filename)
{
    static TextureHolder holder;

    auto& m = holder.m_Textures;

    auto keyValuePair = m.find(filename);
    if (keyValuePair != m.end())
    {
        return keyValuePair->second;
    }
    else
    {
        auto& texture = m[filename];
        texture.loadFromFile(filename);
        return texture;
    }
}
