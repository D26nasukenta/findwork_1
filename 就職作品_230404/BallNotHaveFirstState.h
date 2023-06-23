#pragma once
#include "BallNotHaveState.h"

class ENEMY;

class BallNotHaveFirstState :
    public BallNotHaveState
{

public:
    BallNotHaveFirstState(ENEMY* penemy) : m_Enemy(penemy) {};

    void   Init();
    void   Uninit();
    void   Update();


private:
    ENEMY* m_Enemy;
    int m_Frame = 0;
    int m_Num = 0;
};

