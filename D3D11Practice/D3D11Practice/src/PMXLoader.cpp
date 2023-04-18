#include "PMXLoader.h"
#include<vector>

void PMXLoader::LoadPMX(const char* filePath)
{
	//�V�[�N�|�C���g
	uint32_t seek_point = 3;//�V�O�l�`���̂R�o�C�g����΂��ēǂݍ���
	//�t�@�C���̓ǂݍ���
	std::ifstream Data(filePath, std::ios::binary | std::ios::ate);
	std::streamsize fileSize = Data.tellg();
	//�擪����ǂݍ���
	Data.seekg(std::ios::beg);
	//�o�b�t�@�̍쐬
	std::vector<char> buffer(fileSize);
	//�ւ����̉��
	PMXHeader header;
	memcpy(&header,buffer.data()+seek_point,sizeof(PMXHeader));
}
