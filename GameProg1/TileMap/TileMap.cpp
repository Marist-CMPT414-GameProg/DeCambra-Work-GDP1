#include <SFML/Graphics/RenderTarget.hpp>
#include "TileMap.h"

using sf::FloatRect;
using sf::RenderStates;
using sf::RenderTarget;
using sf::Triangles;
using sf::Vector2u;
using sf::Vector2f;
using sf::Vertex;
using std::make_unique;

int
TileMap::intersects(sf::FloatRect otherCollider)
{
    int collisionCount = 0;
    for (int k = 0; k < m_vertices.getVertexCount() / 6; ++k) {
        if (colliding[k]) {
            FloatRect tileCollider(m_vertices[k * 6].position, tileSize);
            collisionCount += tileCollider.intersects(otherCollider) ? 1 : 0;
        }
    }
    return collisionCount;
}

bool
TileMap::load(const std::string& tileset, Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
{
    // load the tileset texture
    if (!m_tileset.loadFromFile(tileset))
        return false;

    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(Triangles);
    m_vertices.resize(width * height * 6);
    colliding = make_unique<bool[]>(width * height);
    this->tileSize = Vector2f(tileSize);

    // populate the vertex array, with two triangles per tile
    for (unsigned int i = 0; i < width; ++i)
        for (unsigned int j = 0; j < height; ++j)
        {
            // get the current tile number
            int tileNumber = tiles[i + j * width];

            colliding[i + j * width] = tileNumber > 0;

            // find its position in the tileset texture
            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            // get a pointer to the triangles' vertices of the current tile
            Vertex* triangles = &m_vertices[(i + j * width) * 6];

            // define the 6 corners of the two triangles
            triangles[0].position = Vector2f(i * tileSize.x, j * tileSize.y);
            triangles[1].position = Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            triangles[2].position = Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
            triangles[3].position = Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
            triangles[4].position = Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            triangles[5].position = Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);

            // define the 6 matching texture coordinates
            triangles[0].texCoords = Vector2f(tu * tileSize.x, tv * tileSize.y);
            triangles[1].texCoords = Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            triangles[2].texCoords = Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            triangles[3].texCoords = Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            triangles[4].texCoords = Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            triangles[5].texCoords = Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
        }

    return true;
}

void
TileMap::draw(RenderTarget& target, RenderStates states) const
{
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = &m_tileset;

    // draw the vertex array
    target.draw(m_vertices, states);
}