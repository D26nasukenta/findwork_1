#pragma once
#include "scene.h"
class TitleSecond :
    public Scene
{
    void Init();
    void Uninit();
    void Update();

private:

    class Transition* transition = NULL;

};

