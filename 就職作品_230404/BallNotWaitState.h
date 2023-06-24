#pragma once
#include "BallNotHaveState.h"

class ENEMY;

class BallNotWaitState :
    public BallNotHaveState
{


public:
    BallNotWaitState(ENEMY* penemy) : m_Enemy(penemy) {};

    void   Init();
    void   Uninit();
    void   Update();


private:
    ENEMY* m_Enemy;
    int m_Frame = 0;


};

