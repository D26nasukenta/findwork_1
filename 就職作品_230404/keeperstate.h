#pragma once
class KeeperState
{
private:

protected:
	int StateCount = 0;
public:
	KeeperState() {}

	virtual ~KeeperState() {}

	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual int GetState() = 0;
};

