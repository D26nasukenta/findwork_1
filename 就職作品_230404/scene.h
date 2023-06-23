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

	std::list<GameObject*>	m_GameObject[3];//STL�̃��X�g�\��
	
	int m_SceneNumber = 0; 
	//bool m_TutorialScene = false;


public:
	Scene() {}
	virtual ~Scene() {}

	virtual void Init() = 0;

	template<typename T>//�e���v���[�g�֐�
	T* AddGameObject(int Layer)
	{
		T* GameObject = new T();
		m_GameObject[Layer].push_back(GameObject);
		GameObject->Init();

		return GameObject;
	}

	template<typename T>//�e���v���[�g�֐�
	T* GetGameObject(int Layer)
	{

			for (GameObject* object : m_GameObject[Layer])
			{
				if (typeid(*object) == typeid(T))//�^�𒲂ׂ�(RTTI���I�^���)
				{

					return (T*)object;

				}
			
			}
		
			return NULL;
	}

	template<typename T>//�e���v���[�g�֐�
	std::vector <T*> GetGameObjects(int Layer)
	{
		std::vector<T*> objects;

			for (GameObject* object : m_GameObject[Layer])
			{
				if (typeid(*object) == typeid(T))//�^�𒲂ׂ�(RTTI���I�^���)
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

			for (GameObject* object : m_GameObject[i])//object�|�C���^��m_GameObject�ɓ����Ă镪������
			{
				object->Uninit();
				delete object;
			}
			m_GameObject[i].clear();//���X�g�̃N���A

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
	//�����_��
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