#pragma once
#include<vector>
#include<functional>


class JobScheguler
{
public:
	static void Update();
	static void Render();
	static void RegisterUpdateMethod(std::function<void(void)> func);
	static void RegisterRenderMethod(std::function<void()> func);

private:
	static inline std::vector<std::function<void(void)>> m_fUpdateArray;
	static inline std::vector<std::function<void()>> m_fRenderArray;
};

