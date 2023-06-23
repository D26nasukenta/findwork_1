#pragma once
#include "ballstate.h"
class FootBall;
class ShootBallState :
    public BallState
{
public:
    ShootBallState(FootBall* pfootball) : m_FootBall(pfootball) {};

    void   Init();
    void   Uninit();
    void   Update();


private:
    FootBall* m_FootBall;
    int m_Frame = 0;

};

