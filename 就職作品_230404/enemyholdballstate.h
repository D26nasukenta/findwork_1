#pragma once
#include "ballstate.h"
class FootBall;
class EnemyHoldBallState : public BallState
{
public:
   EnemyHoldBallState (FootBall* pfootball) : m_FootBall(pfootball) {};

    void   Init();
    void   Uninit();
    void   Update();


private:
    FootBall* m_FootBall;
    int m_Frame = 0;


};

