#include "SceneObject.h"

SceneObject::SceneObject()
{
}

SceneObject::~SceneObject()
{
}

void SceneObject::LoadModeldata(std::string modelname, std::string modelfilepath)
{
	ModelData data;
	LoadModel(modelfilepath.c_str(), data);
	m_ModelArray[modelname] = data;
}

ModelData SceneObject::GetModeldata(std::string modelname)
{
	return m_ModelArray[modelname];
}
