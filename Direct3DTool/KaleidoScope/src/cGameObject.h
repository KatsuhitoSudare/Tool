#pragma once
#include "cObject.h"
#include"cTransform.h"
#include"cComponent.h"

namespace KALEIDOSCOPE
{
	class cGameObject : public cObject
	{
	public:
		cGameObject();
		virtual ~cGameObject();

		unique_ptr<cTransform> m_Transform;

		void Init();

		void Render();


		template<typename T>
		T* GetComponent();

		template<typename T>
		void AddComponent();

		virtual void OnAddComponent(){};



	private:
		vector<unique_ptr<cComponent>> m_ComponentVector;

	};



	template<typename T>
	inline T* cGameObject::GetComponent()
	{
		T* temp = nullptr;

		for (auto it = m_ComponentVector.begin();it != m_ComponentVector.end();it++)
		{
			temp = dynamic_cast<T*>(it);
			if (temp)
			{
				return temp;
			}
		}
		
		return nullptr;
	}


	template<typename T>
	inline void cGameObject::AddComponent()
	{
		m_ComponentVector.emplace_back(std::make_unique(T));
	}
}



