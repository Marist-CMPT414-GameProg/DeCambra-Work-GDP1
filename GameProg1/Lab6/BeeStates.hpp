#ifndef HPP_BEE_STATES
#define HPP_BEE_STATES

#include "Bee.hpp"

struct Bee::State
{
	State(Bee& bee);
	virtual void enter() = 0;
	virtual void exit() = 0;
	virtual State* handleEvent(TriggerEvent const&) = 0;
	virtual void update(float dt) = 0;
	Bee& controlledBee;
};

// TODO Declare the inner-structs for the Bee states here

struct Bee::IdleState : public Bee::State
{
	IdleState(Bee& bee);
	void enter();
	void exit();
	State* handleEvent(TriggerEvent const&);
	void update(float dt);
};

struct Bee::OrbitState : public Bee::State
{
	OrbitState(Bee& bee);
	void enter() override;
	void exit() override;
	State* handleEvent(TriggerEvent const&) override;
	void update(float dt) override;
};

struct Bee::WanderState : public Bee::State
{
	WanderState(Bee& bee);
	void enter() override;
	void exit() override;
	State* handleEvent(TriggerEvent const&) override;
	void update(float dt) override;
};

#endif HPP_BEE_STATES