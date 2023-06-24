#pragma once
#include "scene.h"
class Game :
    public Scene
{
    void Init();
    void Uninit();
    void Update();
private:

    class Transition* transition = NULL;
    bool changemode = false;
};

