#include "ResourceManager.h"

void ResourceManager::LoadModelData(std::string modelname,std::string filepath)
{
	LoadModel(filepath, m_Modeldata[modelname]);
}

ModelData* ResourceManager::GetModelData(std::string modelname)
{
	return &m_Modeldata[modelname];
}

void ResourceManager::LoadVertexShader(std::string shadername, const wchar_t* Shaderpath)
{
	m_Vshader[shadername].InitVertexShader(Shaderpath);
}

void ResourceManager::LoadPixelShader(std::string shadername, const wchar_t* Shaderpath)
{
	m_PShader[shadername].InitPixelShader(Shaderpath);
}

void ResourceManager::SetShader(std::string Vshadername, std::string Pshadername)
{
	m_Vshader[Vshadername].SetVertexShaderAndInputLayout();
	m_PShader[Pshadername].SetPixelShader();
}
