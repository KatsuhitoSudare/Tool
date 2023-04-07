#include "FBXLoader.h"
#include<iostream>
#include<fstream>
#include<vector>
#include<Windows.h>

#define MAGICNUMBERWIDTH 23				//マジックナンバーの幅
#define HEADERWIDTH (MAGICNUMBERWIDTH + sizeof(int32_t))
#define NODEENDMARK7_4 sizeof(char) * 13//ノード終了マーカーのサイズVer7.4
#define NODEENDMARK7_5 sizeof(char) * 25//ノード終了マーカーのサイズVer7.5


using namespace std;

// FBXファイルのヘッダー情報
struct FbxHeader {
	int32_t version; // バージョン番号
	int32_t magic;   // マジックナンバー
};

struct ArrayFormat
{

};




// FBXファイルのノード情報4ByteVer
struct FbxNode {
	std::string name; // ノード名
	int32_t type;     // ノードタイプ
	int32_t flags;    // フラグ
	int32_t num_props; // プロパティ数
};

// FBXファイルのプロパティ情報
struct FbxProperty {
	int32_t type;   // プロパティタイプ
	int32_t length; // プロパティ長
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
	//バイナリ形式で読み込む
	ifstream FBXBinary(FilePath, ios::binary | ios::ate);
	if (!FBXBinary)
	{
		//エラー
		cout << "ファイルパスが無効です" << endl;
	}
	//サイズを確認
	std::streamsize FileSize = FBXBinary.tellg();
	//先頭からシーク
	FBXBinary.seekg(0, std::ios::beg);
	//サイズ分の領域を確保
	vector<char> buffer(FileSize);
	if (!FBXBinary.read(buffer.data(), FileSize))
	{
		//エラー
		cout << "読み込みに失敗" << endl;
	}

	// ヘッダー情報を解析する
	FbxHeader header;
	memcpy(&header.version, buffer.data() + sizeof(char) * MAGICNUMBERWIDTH, sizeof(header.version));

#ifdef _DEBUG
	printf("バージョン%d\n", header.version);
#endif // _DEBUG

	// FBXHeaderExtension情報を解析する
	FBXHeaderExtension headerExt;
	memcpy(&headerExt.offset, buffer.data() + HEADERWIDTH, sizeof(headerExt.offset));
	memcpy(&headerExt.PropertyNum, buffer.data() + HEADERWIDTH + sizeof(headerExt.offset), sizeof(headerExt.PropertyNum));
	memcpy(&headerExt.PropertyByteWide, buffer.data() + HEADERWIDTH + sizeof(headerExt.offset) + sizeof(headerExt.PropertyNum), sizeof(headerExt.PropertyByteWide));

#ifdef _DEBUG
	printf("FBXHeaderExtension情報：\n");
	printf("Offset: %d\n", headerExt.offset);
	printf("Property数: %d\n", headerExt.PropertyNum);
	printf("Property Byte幅: %d\n", headerExt.PropertyByteWide);
#endif

    // ノード情報を解析する
    int32_t pos = HEADERWIDTH + headerExt.offset;
    while (pos < FileSize) {
        FbxNode node;
        // ノード名を読み込む
        int32_t name_length;
        memcpy(&name_length, buffer.data() + pos, sizeof(name_length));
        printf("%x", name_length);

        pos += sizeof(name_length + '\0');
        name_length += '\0';
        node.name = std::string(buffer.data() + pos, name_length);
        pos += name_length;

        // ノードタイプを読み込む
        memcpy(&node.type, buffer.data() + pos, sizeof(node.type));
        pos += sizeof(node.type);

        // フラグを読み込む
        memcpy(&node.flags, buffer.data() + pos, sizeof(node.flags));
        pos += sizeof(node.flags);

        // プロパティ数を読み込む
        memcpy(&node.num_props, buffer.data() + pos, sizeof(node.num_props));
        pos += sizeof(node.num_props);

        // プロパティ情報を解析する
        for (int i = 0; i < node.num_props; ++i) {
            FbxProperty prop;
            memcpy(&prop.type, buffer.data() + pos, sizeof(prop.type));
            pos += sizeof(prop.type);
            memcpy(&prop.length, buffer.data() + pos, sizeof(prop.length));
            pos += sizeof(prop.length);
            // プロパティの実際のデータを読み込む
            // prop.length 分だけデータを読み込む
            std::vector<char> propData(prop.length);
            memcpy(propData.data(), buffer.data() + pos, prop.length);
            pos += prop.length;
        }

        // 子ノードの情報を読み込む
        int32_t num_children;
        memcpy(&num_children, buffer.data() + pos, sizeof(num_children));
        pos += sizeof(num_children);
        for (int i = 0; i < num_children; ++i) {
            // 子ノードの情報を読み込む
            // ここでは再帰的に関数を呼び出すだけの例を示す
            LoadFBX(FilePath);
        }

        // ノード終了マーカーを読み込む
        if (header.version < 7500) {
            pos += NODEENDMARK7_4;
        }
        else {
            pos += NODEENDMARK7_5;
        }
    }

}
