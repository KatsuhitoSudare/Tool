#pragma once

class GameObject;
class Component
{
public:
	Component() = delete;
	Component(GameObject* object);
	virtual ~Component();
	virtual void Init() {};

protected:
	GameObject* m_pGamobject;
};

