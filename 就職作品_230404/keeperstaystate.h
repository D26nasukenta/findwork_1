#pragma once
#include "keeperstate.h"
class GoalKeeper;
class KeeperStayState :
    public KeeperState
{
public:
    KeeperStayState(GoalKeeper* pgoalkeeper) : m_Keeper(pgoalkeeper) {};

    void   Init();
    void   Uninit();
    void   Update();
    int    GetState()
    {
        return StateCount;
    };


private:
    GoalKeeper* m_Keeper;
    int m_Frame = 0;
};

