#pragma once
#include "state.h"
class ENEMY;
class DiscoverState :
    public State
{
public:
    DiscoverState(ENEMY* penemy) : m_Enemy(penemy) {};

    void   Init();
    void   Uninit();
    void   Update();
    int    GetState()
    {
        return StateCount;
    };

private:
    ENEMY* m_Enemy;
    int m_Frame = 0 , m_Random = 0;
    float GoalLength = 0.0f;
    D3DXVECTOR3 playerPos;

};

