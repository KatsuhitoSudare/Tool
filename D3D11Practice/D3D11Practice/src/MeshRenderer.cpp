#include "MeshRenderer.h"
#include"JobScheguler.h"
#include<utility>
#include"ResourceManager.h"
#include"GameObject.h"

MeshRenderer::~MeshRenderer()
{

}

void MeshRenderer::Init()
{
	std::function<void()> fn = std::bind(&MeshRenderer::Render, this);
	JobScheguler::RegisterRenderMethod(fn);

	ModelData* deta = ResourceManager::GetModelData(m_pGamobject->m_sModelName.c_str());

	for (size_t i = 0; i < deta->Meshes.size(); i++)
	{
		VertexBuffer<Vertex> vb;
		vb.CreateVertexBuffer(deta->Meshes[i].vertices);
		m_Vertex.push_back(vb);
	}

	m_cbWVP.CreateConstantBuffer();
	m_cbMaterial.CreateConstantBuffer();
	m_cbDirLite.CreateConstantBuffer();
}

void MeshRenderer::Render()
{



	ResourceManager::SetShader("SimpleVs","SimplePs");
}
