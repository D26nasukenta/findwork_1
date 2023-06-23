#pragma once
#include "scene.h"
class Result :
    public Scene
{
    void Init();
    void Uninit();
    void Update();
    int GetSelection()
    {
        return Selection;
    }

private:

    class Transition* transition = NULL;
    bool changemode = false;
    int Selection = 0;

};

