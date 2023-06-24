#pragma once
//Šî’êƒNƒ‰ƒX
class State
{

private:

protected:

	int StateCount = 0;

public:
	State() {}

	virtual ~State() {}

	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual int GetState() = 0;

	

};

