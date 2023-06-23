#pragma once
#include "scene.h"

class Tutorial :
    public Scene
{
    void Init();
    void Uninit();
    void Update();


private:

    class Transition* transition = NULL;
    bool m_key = false;
};

