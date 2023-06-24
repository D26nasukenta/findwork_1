#pragma once
#include "ballstate.h"
class FootBall;
class CHeckBallState :
    public BallState
{
public:
    CHeckBallState(FootBall* pfootball) : m_FootBall(pfootball) {};

    void   Init();
    void   Uninit();
    void   Update();


private:
    FootBall* m_FootBall;
    int m_Frame = 0;


};

