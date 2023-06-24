#pragma once
//Šî’êƒNƒ‰ƒX
class BallNotHaveState
{

private:

protected:

	int StateCount = 0;

public:
	BallNotHaveState() {}

	virtual ~BallNotHaveState() {}

	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;

};

