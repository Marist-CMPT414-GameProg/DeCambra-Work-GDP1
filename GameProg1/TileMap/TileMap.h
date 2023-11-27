#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:

    int intersects(sf::FloatRect collider);
    
    bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    std::unique_ptr<bool[]> colliding;
    sf::Vector2f tileSize;

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};