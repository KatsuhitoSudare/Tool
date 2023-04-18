#include "PMXLoader.h"
#include<vector>

void PMXLoader::LoadPMX(const char* filePath)
{
	//シークポイント
	uint32_t seek_point = 3;//シグネチャの３バイト分飛ばして読み込む
	//ファイルの読み込み
	std::ifstream Data(filePath, std::ios::binary | std::ios::ate);
	std::streamsize fileSize = Data.tellg();
	//先頭から読み込む
	Data.seekg(std::ios::beg);
	//バッファの作成
	std::vector<char> buffer(fileSize);
	//へっだの解析
	PMXHeader header;
	memcpy(&header,buffer.data()+seek_point,sizeof(PMXHeader));
}
