#include "JobScheguler.h"

void JobScheguler::Update()
{
	for (auto it = m_fUpdateArray.begin(); it != m_fUpdateArray.end(); it++)
	{
		if ((*it) != nullptr)
		{
			(*it)();
		}
		else
		{
			m_fUpdateArray.erase(it);
		}
	}
}

void JobScheguler::Render()
{
	for (auto it = m_fRenderArray.begin(); it != m_fRenderArray.end(); it++)
	{
		if ((*it) != nullptr)
		{
			(*it)();
		}
		else
		{
			m_fRenderArray.erase(it);
		}
	}
}

void JobScheguler::RegisterUpdateMethod(std::function<void()> func)
{
	m_fUpdateArray.push_back(func);
}

void JobScheguler::RegisterRenderMethod(std::function<void()> func)
{
	m_fRenderArray.push_back(func);
}
