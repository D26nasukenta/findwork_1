#pragma once
class GameObject;
class Command
{
public:
	virtual ~Command(){}

	virtual void execute(GameObject* gameobject) = 0;
};

