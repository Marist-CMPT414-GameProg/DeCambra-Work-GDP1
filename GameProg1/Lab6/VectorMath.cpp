#include "VectorMath.hpp"

float dot(sf::Vector2f const& a, sf::Vector2f const& b)
{
    return a.x * b.x + a.y * b.y;
}

float dot(sf::Vector3f const& a, sf::Vector3f const& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float sqr_magnitude(sf::Vector2f const& a)
{
    return dot(a, a);
}

float sqr_magnitude(sf::Vector3f const& a)
{
    return dot(a, a);
}

float magnitude(sf::Vector2f const& a)
{
    return std::sqrt(sqr_magnitude(a));
}

float magnitude(sf::Vector3f const& a)
{
    return std::sqrt(sqr_magnitude(a));
}

void normalize(sf::Vector2f& a)
{
    if (a.x == 0 && a.y == 0) { return; }
    a /= magnitude(a);
}

void normalize(sf::Vector3f& a)
{
    if (a.x == 0 && a.y == 0 && a.z == 0) { return; }
    a /= magnitude(a);
}

sf::Vector2f normalized(sf::Vector2f const& a)
{
    float d = magnitude(a);
    return sf::Vector2f(a.x / d, a.y / d);
}

sf::Vector3f normalized(sf::Vector3f const& a)
{
    float d = magnitude(a);
    return sf::Vector3f(a.x / d, a.y / d, a.z / d);
}

bool is_zero_approx(sf::Vector2f const& a, float epsilon)
{
    return sqr_magnitude(a) < epsilon;
}
