#pragma once

class Observer 
{
public:
    virtual void onLevelChanged(int newLevel) = 0;
};
