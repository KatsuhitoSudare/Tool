#include "Trunsform.h"

Trunsform::~Trunsform()
{
}

DirectX::XMVECTOR Trunsform::GetPosition()
{
	return Pos;
}

DirectX::XMVECTOR Trunsform::GetScale()
{
	return Scale;
}

DirectX::XMVECTOR Trunsform::GetRoutate()
{
	return Rotate;
}

void Trunsform::SetPosition(DirectX::XMVECTOR pos)
{
	Pos = pos;
}

void Trunsform::SetScale(DirectX::XMVECTOR scl)
{
	Scale = scl;
}

void Trunsform::SetRotate(DirectX::XMVECTOR rot)
{
	Rotate = rot;
}
