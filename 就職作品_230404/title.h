#pragma once
#include "scene.h"
class Title :
    public Scene
{
    void Init();
    void Uninit();
    void Update();

private:

    class Transition* transition = NULL;

};

