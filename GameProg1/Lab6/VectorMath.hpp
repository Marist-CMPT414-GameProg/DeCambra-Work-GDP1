#ifndef HPP_VECTORMATH
#define HPP_VECTORMATH

#include <cmath>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>

/// <summary>
/// Determines the "signed-ness" of a value.
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="val"></param>
/// <returns></returns>
template <typename T>
int signum(T val)
{
    return (T(0) < val) - (val < T(0));
}

float dot(sf::Vector2f const& a, sf::Vector2f const& b);

float dot(sf::Vector3f const& a, sf::Vector3f const& b);

float sqr_magnitude(sf::Vector2f const& a);

float sqr_magnitude(sf::Vector3f const& a);

float magnitude(sf::Vector2f const& a);

float magnitude(sf::Vector3f const& a);

void normalize(sf::Vector2f& a);

void normalize(sf::Vector3f& a);

sf::Vector2f normalized(sf::Vector2f const& a);

sf::Vector3f normalized(sf::Vector3f const& a);

bool is_zero_approx(sf::Vector2f const& a, float epsilon = 0.000001);

#endif HPP_VECTORMATH