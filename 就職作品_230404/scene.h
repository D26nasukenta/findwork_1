#pragma once
#include <list>
#include <vector>
#include<typeinfo>

#include "gameobject.h"
#include "input.h"


class Scene
{
protected:
	//	GameObject* m_GameObject[OBJECT_NUM];

	std::list<GameObject*>	m_GameObject[3];//STLのリスト構造
	
	int m_SceneNumber = 0; 
	//bool m_TutorialScene = false;


public:
	Scene() {}
	virtual ~Scene() {}

	virtual void Init() = 0;

	template<typename T>//テンプレート関数
	T* AddGameObject(int Layer)
	{
		T* GameObject = new T();
		m_GameObject[Layer].push_back(GameObject);
		GameObject->Init();

		return GameObject;
	}

	template<typename T>//テンプレート関数
	T* GetGameObject(int Layer)
	{

			for (GameObject* object : m_GameObject[Layer])
			{
				if (typeid(*object) == typeid(T))//型を調べる(RTTI動的型情報)
				{

					return (T*)object;

				}
			
			}
		
			return NULL;
	}

	template<typename T>//テンプレート関数
	std::vector <T*> GetGameObjects(int Layer)
	{
		std::vector<T*> objects;

			for (GameObject* object : m_GameObject[Layer])
			{
				if (typeid(*object) == typeid(T))//型を調べる(RTTI動的型情報)
				{

					objects.push_back((T*)object);


				}

			}

		return objects;
	}

	virtual void Uninit()
	{
		
		for (int i = 0; i < 3; i++)
		{

			for (GameObject* object : m_GameObject[i])//objectポインタをm_GameObjectに入ってる分だけ回す
			{
				object->Uninit();
				delete object;
			}
			m_GameObject[i].clear();//リストのクリア

		}
	}

	virtual void Update()
	{
		for (int  i = 0; i < 3; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				object->Update();
			}
			m_GameObject[i].remove_if([](GameObject* object){return object->Destroy(); });
		}
	//ラムダ式
	}

	virtual void Draw()
	{
		for (int i = 0; i<3;i++)
		{

			for (GameObject* object : m_GameObject[i])
			{
				object->Draw();
			}
		
		}
	}

	 void SetSceneNumber(int i)
	{

			m_SceneNumber = i;
	}
	
	 int GetSceneNumber()
	 {
		 return m_SceneNumber;
	 }

	 //bool GetTutorial()
	 //{
		// return m_TutorialScene;
	 //}
};