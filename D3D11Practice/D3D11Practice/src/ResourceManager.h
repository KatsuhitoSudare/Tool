#pragma once
#include"ModelLoader.h"
#include"Direct3D11/VertexShader.h"
#include"Direct3D11/PixelShader.h"

class ResourceManager
{
public:
	static void LoadModelData(std::string modelname, std::string filepath);
	static ModelData* GetModelData(std::string modelname);
	static void LoadVertexShader(std::string shadername,const wchar_t* Shaderpath);
	static void LoadPixelShader(std::string shadername, const wchar_t* Shaderpath);
	static void SetShader(std::string Vshadername, std::string Pshadername);
private:
	static inline std::unordered_map<std::string, ModelData> m_Modeldata;
	static inline std::unordered_map<std::string, VertexShader>m_Vshader;
	static inline std::unordered_map<std::string, PixelShader>m_PShader;
};

