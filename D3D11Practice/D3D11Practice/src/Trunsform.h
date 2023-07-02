#pragma once
#include "Component.h"
#include<DirectXMath.h>


class Trunsform :public Component
{
public:
	using Component::Component;
	~Trunsform();
	DirectX::XMVECTOR GetPosition();
	DirectX::XMVECTOR GetScale();
	DirectX::XMVECTOR GetRoutate();

	void SetPosition(DirectX::XMVECTOR pos);
	void SetScale(DirectX::XMVECTOR scl);
	void SetRotate(DirectX::XMVECTOR rot);

private:
	DirectX::XMVECTOR Pos;
	DirectX::XMVECTOR Scale;
	DirectX::XMVECTOR Rotate;
};

