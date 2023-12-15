#pragma once
#include "PlayableCharacter.h"
#include "Observer.h"

class John : public PlayableCharacter, public Observer
{
private:
	bool WASD;
public:
	// A constructor specific to John
	John();

	// The overriden input handler for JOhn
	bool virtual handleInput();

	// Implement the LevelObserver interface
	virtual void onLevelChanged(int newLevel) override;
};