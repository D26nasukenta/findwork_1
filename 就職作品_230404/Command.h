#pragma once
class GameObject;
class Command
{
public:
	virtual ~Command(){}

	virtual void execute(GameObject* gameobject) = 0;
protected:
	int m_shotFrame = 0;
};

