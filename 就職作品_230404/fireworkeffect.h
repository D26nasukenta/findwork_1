#pragma once
#include "effect.h"
class FireWorkEffect :  public Effect
{
public:
    void Init() override;
    void Uninit() override;
    void Update() override;
    void Draw() override;

};

