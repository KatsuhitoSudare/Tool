#include "FBXLoader.h"
#include<iostream>
#include<fstream>
#include<vector>
#include<Windows.h>

#define MAGICNUMBERWIDTH 23				//�}�W�b�N�i���o�[�̕�
#define HEADERWIDTH (MAGICNUMBERWIDTH + sizeof(int32_t))
#define NODEENDMARK7_4 sizeof(char) * 13//�m�[�h�I���}�[�J�[�̃T�C�YVer7.4
#define NODEENDMARK7_5 sizeof(char) * 25//�m�[�h�I���}�[�J�[�̃T�C�YVer7.5


using namespace std;

// FBX�t�@�C���̃w�b�_�[���
struct FbxHeader {
	int32_t version; // �o�[�W�����ԍ�
	int32_t magic;   // �}�W�b�N�i���o�[
};

struct ArrayFormat
{

};




// FBX�t�@�C���̃m�[�h���4ByteVer
struct FbxNode {
	std::string name; // �m�[�h��
	int32_t type;     // �m�[�h�^�C�v
	int32_t flags;    // �t���O
	int32_t num_props; // �v���p�e�B��
};

// FBX�t�@�C���̃v���p�e�B���
struct FbxProperty {
	int32_t type;   // �v���p�e�B�^�C�v
	int32_t length; // �v���p�e�B��
};

//FBXHeaderExtension
struct FBXHeaderExtension
{
	int32_t offset;
	int32_t PropertyNum;
	int32_t PropertyByteWide;

};




void LoadFBX(const char* FilePath)
{
	//�o�C�i���`���œǂݍ���
	ifstream FBXBinary(FilePath, ios::binary | ios::ate);
	if (!FBXBinary)
	{
		//�G���[
		cout << "�t�@�C���p�X�������ł�" << endl;
	}
	//�T�C�Y���m�F
	std::streamsize FileSize = FBXBinary.tellg();
	//�擪����V�[�N
	FBXBinary.seekg(0, std::ios::beg);
	//�T�C�Y���̗̈���m��
	vector<char> buffer(FileSize);
	if (!FBXBinary.read(buffer.data(), FileSize))
	{
		//�G���[
		cout << "�ǂݍ��݂Ɏ��s" << endl;
	}

	// �w�b�_�[������͂���
	FbxHeader header;
	memcpy(&header.version, buffer.data() + sizeof(char) * MAGICNUMBERWIDTH, sizeof(header.version));

#ifdef _DEBUG
	printf("�o�[�W����%d\n", header.version);
#endif // _DEBUG

	// FBXHeaderExtension������͂���
	FBXHeaderExtension headerExt;
	memcpy(&headerExt.offset, buffer.data() + HEADERWIDTH, sizeof(headerExt.offset));
	memcpy(&headerExt.PropertyNum, buffer.data() + HEADERWIDTH + sizeof(headerExt.offset), sizeof(headerExt.PropertyNum));
	memcpy(&headerExt.PropertyByteWide, buffer.data() + HEADERWIDTH + sizeof(headerExt.offset) + sizeof(headerExt.PropertyNum), sizeof(headerExt.PropertyByteWide));

#ifdef _DEBUG
	printf("FBXHeaderExtension���F\n");
	printf("Offset: %d\n", headerExt.offset);
	printf("Property��: %d\n", headerExt.PropertyNum);
	printf("Property Byte��: %d\n", headerExt.PropertyByteWide);
#endif

    // �m�[�h������͂���
    int32_t pos = HEADERWIDTH + headerExt.offset;
    while (pos < FileSize) {
        FbxNode node;
        // �m�[�h����ǂݍ���
        int32_t name_length;
        memcpy(&name_length, buffer.data() + pos, sizeof(name_length));
        printf("%x", name_length);

        pos += sizeof(name_length + '\0');
        name_length += '\0';
        node.name = std::string(buffer.data() + pos, name_length);
        pos += name_length;

        // �m�[�h�^�C�v��ǂݍ���
        memcpy(&node.type, buffer.data() + pos, sizeof(node.type));
        pos += sizeof(node.type);

        // �t���O��ǂݍ���
        memcpy(&node.flags, buffer.data() + pos, sizeof(node.flags));
        pos += sizeof(node.flags);

        // �v���p�e�B����ǂݍ���
        memcpy(&node.num_props, buffer.data() + pos, sizeof(node.num_props));
        pos += sizeof(node.num_props);

        // �v���p�e�B������͂���
        for (int i = 0; i < node.num_props; ++i) {
            FbxProperty prop;
            memcpy(&prop.type, buffer.data() + pos, sizeof(prop.type));
            pos += sizeof(prop.type);
            memcpy(&prop.length, buffer.data() + pos, sizeof(prop.length));
            pos += sizeof(prop.length);
            // �v���p�e�B�̎��ۂ̃f�[�^��ǂݍ���
            // prop.length �������f�[�^��ǂݍ���
            std::vector<char> propData(prop.length);
            memcpy(propData.data(), buffer.data() + pos, prop.length);
            pos += prop.length;
        }

        // �q�m�[�h�̏���ǂݍ���
        int32_t num_children;
        memcpy(&num_children, buffer.data() + pos, sizeof(num_children));
        pos += sizeof(num_children);
        for (int i = 0; i < num_children; ++i) {
            // �q�m�[�h�̏���ǂݍ���
            // �����ł͍ċA�I�Ɋ֐����Ăяo�������̗������
            LoadFBX(FilePath);
        }

        // �m�[�h�I���}�[�J�[��ǂݍ���
        if (header.version < 7500) {
            pos += NODEENDMARK7_4;
        }
        else {
            pos += NODEENDMARK7_5;
        }
    }

}
