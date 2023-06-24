#pragma once
class BallState
{


private:


public:
	BallState() {}

	virtual ~BallState() {}

	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;

};

