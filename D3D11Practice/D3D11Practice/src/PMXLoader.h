#pragma once
#include<fstream>
#include<iostream>
#include<string>

struct PMXHeader
{
	float version; // 例： 00 00 80 3 F == 1. 00 
	char model_name[20]; // モデル 名 
	char comment[256]; // モデル コメント
};

class PMXLoader
{
public:
	void LoadPMX(const char* filePath);
private:

};

