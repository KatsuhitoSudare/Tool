#pragma once

class GameObject;
class Component
{
public:
	Component() = delete;
	Component(GameObject* object);
	virtual ~Component();

protected:
	GameObject* m_pGamobject;
};

