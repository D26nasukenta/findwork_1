#pragma once
class Command;

class InputHandler
{
public:
    Command* handleinput();


private:
    Command* Button_A;
    Command* Button_W;
    Command* Button_S;
    Command* Button_D;
};

