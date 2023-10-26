#include "Crate.h"

std::vector<Crate> createCrates(int numCrates, IntRect arena, Texture& crateTexture)
{
    std::vector<Crate> crates;

    for (int i = 0; i < numCrates; i++)
    {
        Crate crate;

        // Generate random positions within the arena
        int x = rand() % (arena.width - 50) + arena.left;
        int y = rand() % (arena.height - 50) + arena.top;

        crate.getSprite().setPosition(x, y);
        crate.getSprite().setTexture(crateTexture);

        crates.push_back(crate);
    }

    return crates;
}