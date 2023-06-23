#pragma once
#include "state.h"
class ENEMY;

class DoState :
    public State
{
public:
    DoState(ENEMY* penemy) : m_Enemy(penemy) {};

    void   Init();
    void   Uninit();
    void   Update();
    int    GetState()
    {
        return StateCount;
    };

private:
   
    ENEMY* m_Enemy;
    int m_Frame = 0;
    int m_Num = 0;

    D3DXVECTOR3 FirstPos = D3DXVECTOR3(0.0f, 0.0f, 5.0f);
};

