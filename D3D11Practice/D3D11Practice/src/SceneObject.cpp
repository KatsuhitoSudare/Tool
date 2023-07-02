#include "SceneObject.h"
#include"JobScheguler.h"
#include"Direct3D11/cDirect3D.h"

SceneObject::SceneObject()
{
}

SceneObject::~SceneObject()
{
}

void SceneObject::SceneObjectUpdate()
{
	JobScheguler::Update();
}

void SceneObject::SceneObjectRender()
{
	cDirect3D::ClearRenderTarget(0.6f, 0.6f, 0.6f);
	JobScheguler::Render();
	cDirect3D::SwapBuffuer();
}

void SceneObject::SceneObjectShutDown()
{

}

