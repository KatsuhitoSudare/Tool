#pragma once
#include<fstream>
#include<iostream>
#include<string>

struct PMXHeader
{
	float version; // ��F 00 00 80 3 F == 1. 00 
	char model_name[20]; // ���f�� �� 
	char comment[256]; // ���f�� �R�����g
};

class PMXLoader
{
public:
	void LoadPMX(const char* filePath);
private:

};

