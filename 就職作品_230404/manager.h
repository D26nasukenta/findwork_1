#pragma once
#include  "scene.h"

class Manager
{

public:

	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	template <typename T>
	static void SetScene()
	{
		//‚à‚µ‘O‚ÌƒV[ƒ“‚ª...
		if (m_Scene)
		{
			m_Scene->Uninit();
			delete m_Scene;
		}
		m_Scene = new T();
		m_Scene->Init();
	}

	static class Scene* GetScene()
	{
		return m_Scene;
	};


	//template <typename T>
	//static void SetScenes(int i)
	//{
	//	m_Scenes[i] = new T();

	//}

	//static class Scene* GetScene( int i)
	//{
	//	return m_Scenes[i];
	//};

private:
	static class Scene* m_Scene;
	//static class Scene* m_Scenes[5];
	//static class State* m_State;
};