#include "GameObject.h"
#include "TextureHolder.h"

using namespace sf;
using namespace std;

GameObject::GameObject(std::string const& textureFilename, sf::Vector2f const& position)
{
	sprite.setTexture(TextureHolder::GetTexture(textureFilename));
	sprite.setOrigin(0.5f * getCollider().getSize());
	sprite.setPosition(position);
}

void GameObject::draw(sf::RenderWindow& win) const
{
	win.draw(sprite);
}

sf::FloatRect GameObject::getCollider() const 
{
	return sprite.getGlobalBounds();
}